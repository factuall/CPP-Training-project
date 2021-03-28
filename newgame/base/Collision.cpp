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
		((B->dest.x - B->pos.x) * (A->pos.y - B->pos.y) - (B->dest.y - B->pos.y) * (A->pos.x - B->pos.x))
		/
		((B->dest.y - B->pos.y) * (A->dest.x - A->pos.x) - (B->dest.x - B->pos.x) * (A->dest.y - A->pos.y));
	float intersectionB =
		((A->dest.x - A->pos.x) * (A->pos.y - B->pos.y) - (A->dest.y - A->pos.y) * (A->pos.x - B->pos.x))
		/
		((B->dest.y - B->pos.y) * (A->dest.x - A->pos.x) - (B->dest.x - B->pos.x) * (A->dest.y - A->pos.y));

	//if distances between 0-1 lines are intersecting
	if (intersection != nullptr && (intersectionA >= 0 && intersectionA <= 1 && intersectionB >= 0 && intersectionB <= 1)) {
		*intersection = sf::Vector2f(A->pos.x + (intersectionA * (A->dest.x - A->pos.x)), A->pos.y + (intersectionA * (A->dest.y - A->pos.y)));
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
	entryPos.x = A->pos.x; entryPos.y = A->pos.y;
	posDiffVector.x = (A->pos.x - B->pos.x); posDiffVector.y = (A->pos.y - B->pos.y);
	return (A->pos.x < B->pos.x + B->width &&
		A->pos.x + A->width > B->pos.x &&
		A->pos.y < B->pos.y + B->height &&
		A->pos.y + A->height > B->pos.y);
	
}
bool Collision::CircleCircle() {
	CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
	CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->pos.x; entryPos.y = A->pos.y;
	posDiffVector.x = B->pos.x; posDiffVector.y = B->pos.y;
	return (distance(A->pos.x, A->pos.y, B->pos.x, B->pos.y) <= (A->radius + B->radius));
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
	int tempX = B->pos.x;
	int tempY = B->pos.y;
	if (B->pos.x < A->pos.x)         tempX = A->pos.x;						// test left edge
	else if (B->pos.x > A->pos.x + A->width) tempX = A->pos.x + A->width;   // right edge
	if (B->pos.y < A->pos.y)         tempY = A->pos.y;						// top edge
	else if (B->pos.y > A->pos.y + A->height) tempY = A->pos.y + A->height; // bottom edge
	//is distance from closest edge smaller than circle radius
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->pos.x; entryPos.y = A->pos.y;
	posDiffVector.x = B->pos.x; posDiffVector.y = B->pos.y;
	return (distance(B->pos.x, B->pos.y, tempX, tempY) <= B->radius);

}
bool Collision::LineBox() {
	LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
	BoxCollider* B = dynamic_cast<BoxCollider*>(colliderB);
	LineCollider up(B->pos.x, B->pos.y, B->pos.x + B->width, B->pos.y),
		down(B->pos.x, B->pos.y + B->height, B->pos.x + B->width, B->pos.y + B->height),
		left(B->pos.x, B->pos.y, B->pos.x, B->pos.y + B->height),
		right(B->pos.x + B->width, B->pos.y, B->pos.x + B->width, B->pos.y + B->height);
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
	if (pointCircle(A->pos.x, A->pos.y, B->pos.x, B->pos.y, B->radius) ||
		pointCircle(A->dest.x, A->dest.y, B->pos.x, B->pos.y, B->radius)) {
		entryPos = sf::Vector2f(A->pos.x, A->pos.y);
		posDiffVector = sf::Vector2f(B->pos.x, B->pos.y);
		return true;
	}
	float lineLength = distance(A->pos.x, A->pos.y, A->dest.x, A->dest.y);
	float dot = (((B->pos.x - A->pos.x) * (A->dest.x - A->pos.x)) + ((B->pos.y - A->pos.y) * (A->dest.y - A->pos.y))) / pow(lineLength, 2);
	float closestX = A->pos.x + (dot * (A->dest.x - A->pos.x));
	float closestY = A->pos.y + (dot * (A->dest.y - A->pos.y));
	//is closest point on the line
	if (!linePoint(A->pos.x, A->pos.y, A->dest.x, A->dest.y, closestX, closestY)) {
		
		return false;
	}
	//if closest point in circle
	entryPos = sf::Vector2f(B->pos.x, B->pos.y);
	posDiffVector = sf::Vector2f(closestX, closestY);
	if (distance(closestX, closestY, B->pos.x, B->pos.y) <= B->radius) return  true;


}

void Collision::getCollisionDetails(sf::Vector2f *result[2])
{
	sf::Vector2f details[2]{entryPos, posDiffVector};
	*result = details;
}

float Collision::distance(sf::Vector2f A, sf::Vector2f B) {
	return sqrt(((A.x - B.x) * (A.x - B.x)) + ((A.y - B.y) * (A.y - B.y)));
}

