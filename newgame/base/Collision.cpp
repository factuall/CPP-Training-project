#include <tgmath.h>

#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"

float Collision::distance(int x, int y, int destX, int destY) {
	return sqrt(((x - destX) * (x - destX)) + ((y - destY) * (y - destY)));
}

bool Collision::linePoint(int x, int y, int destX, int destY, int pointX, int pointY) {
	float dist = distance(pointX, pointY, x, y);
	float distDest = distance(pointX, pointY, destX, destY);
	float lineLength = distance(x, y, destX, destY);
	float buffer = 0.1;
	return (dist + distDest >= lineLength - buffer && dist + distDest <= lineLength + buffer);
}

bool Collision::pointCircle(int x, int y, int circleX, int circleY, int radius) {
	return (distance(x, y, circleX, circleY) <= radius);
}

bool Collision::lineLine(LineCollider* A, LineCollider* B, sf::Vector2f *intersection) {
	//distances to intersection point
	float intersectionA =
		((B->destX - B->x) * (A->y - B->y) - (B->destY - B->y) * (A->x - B->x))
		/
		((B->destY - B->y) * (A->destX - A->x) - (B->destX - B->x) * (A->destY - A->y));
	float intersectionB =
		((A->destX - A->x) * (A->y - B->y) - (A->destY - A->y) * (A->x - B->x))
		/
		((B->destY - B->y) * (A->destX - A->x) - (B->destX - B->x) * (A->destY - A->y));

	//if distances between 0-1 lines are intersecting
	if (intersection != nullptr && (intersectionA >= 0 && intersectionA <= 1 && intersectionB >= 0 && intersectionB <= 1)) {
		*intersection = sf::Vector2f(A->x + (intersectionA * (A->destX - A->x)), A->y + (intersectionA * (A->destY - A->y)));
		return true;
	}
	return (intersectionA >= 0 && intersectionA <= 1 && intersectionB >= 0 && intersectionB <= 1);
}

bool Collision::lineLine(LineCollider* A, LineCollider* B) {
	return lineLine(A, B, nullptr);
}

bool Collision::BoxBox() {
	BoxCollider* A = dynamic_cast<BoxCollider*>(colliderA);
	BoxCollider* B = dynamic_cast<BoxCollider*>(colliderB);
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->x; entryPos.y = A->y;
	posDiffVector.x = (A->x - B->x); posDiffVector.y = (A->y - B->y);
	return (A->x < B->x + B->width &&
		A->x + A->width > B->x &&
		A->y < B->y + B->height &&
		A->y + A->height > B->y);
	
}
bool Collision::CircleCircle() {
	CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
	CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->x; entryPos.y = A->y;
	posDiffVector.x = B->x; posDiffVector.y = B->y;
	return (distance(A->x, A->y, B->x, B->y) <= (A->radius + B->radius));
}
bool Collision::LineLine() {
	LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
	LineCollider* B = dynamic_cast<LineCollider*>(colliderB);
	//distances to intersection point
	entryPos = sf::Vector2f();
	posDiffVector = entryPos;
	return lineLine(A, B, &entryPos);

}
bool Collision::BoxCircle() {
	BoxCollider* A = dynamic_cast<BoxCollider*>(colliderA);
	CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
	int tempX = B->x;
	int tempY = B->y;
	if (B->x < A->x)         tempX = A->x;						// test left edge
	else if (B->x > A->x + A->width) tempX = A->x + A->width;   // right edge
	if (B->y < A->y)         tempY = A->y;						// top edge
	else if (B->y > A->y + A->height) tempY = A->y + A->height; // bottom edge
	//is distance from closest edge smaller than circle radius
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->x; entryPos.y = A->y;
	posDiffVector.x = B->x; posDiffVector.y = B->y;
	return (distance(B->x, B->y, tempX, tempY) <= B->radius);

}
bool Collision::LineBox() {
	LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
	BoxCollider* B = dynamic_cast<BoxCollider*>(colliderB);
	LineCollider up(B->x, B->y, B->x + B->width, B->y),
		down(B->x, B->y + B->height, B->x + B->width, B->y + B->height),
		left(B->x, B->y, B->x, B->y + B->height),
		right(B->x + B->width, B->y, B->x + B->width, B->y + B->height);
	entryPos = sf::Vector2f();
	posDiffVector = sf::Vector2f();
	if (lineLine(A, &up, &entryPos)) {
		lineLine(A, &down, &posDiffVector);
		lineLine(A, &left, &posDiffVector);
		lineLine(A, &right, &posDiffVector);
	}
	else if (lineLine(A, &down, &entryPos)) {
		lineLine(A, &up, &posDiffVector);
		lineLine(A, &left, &posDiffVector);
		lineLine(A, &right, &posDiffVector);
	}
	else if (lineLine(A, &left, &entryPos)) {
		lineLine(A, &up, &posDiffVector);
		lineLine(A, &down, &posDiffVector);
		lineLine(A, &right, &posDiffVector);
	}
	else if (lineLine(A, &right, &entryPos)) {
		lineLine(A, &up, &posDiffVector);
		lineLine(A, &left, &posDiffVector);
		lineLine(A, &down, &posDiffVector);
	}
	return (lineLine(A, &up) || lineLine(A, &down) || lineLine(A, &left) || lineLine(A, &right));
}
bool Collision::LineCircle() {
	LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
	CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
	//line start or destination in circle
	if (pointCircle(A->x, A->y, B->x, B->y, B->radius) ||
		pointCircle(A->destX, A->destY, B->x, B->y, B->radius)) {
		entryPos = sf::Vector2f(A->x, A->y);
		posDiffVector = sf::Vector2f(B->x, B->y);
		return true;
	}
	float lineLength = distance(A->x, A->y, A->destX, A->destY);
	float dot = (((B->x - A->x) * (A->destX - A->x)) + ((B->y - A->y) * (A->destY - A->y))) / pow(lineLength, 2);
	float closestX = A->x + (dot * (A->destX - A->x));
	float closestY = A->y + (dot * (A->destY - A->y));
	//is closest point on the line
	if (!linePoint(A->x, A->y, A->destX, A->destY, closestX, closestY)) {
		
		return false;
	}
	//if closest point in circle
	entryPos = sf::Vector2f(B->x, B->y);
	posDiffVector = sf::Vector2f(closestX, closestY);
	if (distance(closestX, closestY, B->x, B->y) <= B->radius) return  true;


}

void Collision::getCollisionDetails(sf::Vector2f *result[2])
{
	sf::Vector2f details[2]{entryPos, posDiffVector};
	*result = details;
}

float Collision::distance(sf::Vector2f A, sf::Vector2f B) {
	return sqrt(((A.x - B.x) * (A.x - B.x)) + ((A.y - B.y) * (A.y - B.y)));
}

