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
	lineLine(A, B, nullptr);
}

Collision::Collision(BoxCollider *A, BoxCollider *B) {
	colliderA = A; colliderB = B;
	colliding = (A->x < B->x + B->width &&
		A->x + A->width > B->x &&
		A->y < B->y + B->height &&
		A->y + A->height > B->y);
	entryPoint = sf::Vector2f(); relativePoint = sf::Vector2f();
	entryPoint.x = A->x; entryPoint.y = A->y;
	relativePoint.x = B->x; relativePoint.y = B->y;
}
Collision::Collision(CircleCollider* A, CircleCollider* B) {
	colliderA = A; colliderB = B;
	colliding = (distance(A->x, A->y, B->x, B->y) <= (A->radius + B->radius));
	entryPoint = sf::Vector2f(); relativePoint = sf::Vector2f();
	entryPoint.x = A->x; entryPoint.y = A->y;
	relativePoint.x = B->x; relativePoint.y = B->y;
}
Collision::Collision(LineCollider* A, LineCollider* B) {
	colliderA = A; colliderB = B;
	//distances to intersection point
	entryPoint = sf::Vector2f();
	colliding = lineLine(A, B, &entryPoint);
	relativePoint = entryPoint;
}
Collision::Collision(BoxCollider* A, CircleCollider* B) {
	colliderA = A; colliderB = B;
	int tempX = B->x;
	int tempY = B->y;
	if (B->x < A->x)         tempX = A->x;						// test left edge
	else if (B->x > A->x + A->width) tempX = A->x + A->width;   // right edge
	if (B->y < A->y)         tempY = A->y;						// top edge
	else if (B->y > A->y + A->height) tempY = A->y + A->height; // bottom edge
	//is distance from closest edge smaller than circle radius
	colliding = (distance(B->x, B->y, tempX, tempY) <= B->radius);
	entryPoint = sf::Vector2f(); relativePoint = sf::Vector2f();
	entryPoint.x = A->x; entryPoint.y = A->y;
	relativePoint.x = B->x; relativePoint.y = B->y;
}
Collision::Collision(LineCollider* A, BoxCollider* B) {
	colliderA = A; colliderB = B;
	LineCollider up(B->x, B->y, B->x + B->width, B->y),
		down(B->x, B->y + B->height, B->x + B->width, B->y + B->height),
		left(B->x, B->y, B->x, B->y + B->height),
		right(B->x + B->width, B->y, B->x + B->width, B->y + B->height);
	entryPoint = sf::Vector2f();
	relativePoint = sf::Vector2f();
	if (lineLine(A, &up, &entryPoint)) {
		lineLine(A, &down, &relativePoint);
		lineLine(A, &left, &relativePoint);
		lineLine(A, &right, &relativePoint);
	}
	else if (lineLine(A, &down, &entryPoint)) {
		lineLine(A, &up, &relativePoint);
		lineLine(A, &left, &relativePoint);
		lineLine(A, &right, &relativePoint);
	}
	else if (lineLine(A, &left, &entryPoint)) {
		lineLine(A, &up, &relativePoint);
		lineLine(A, &down, &relativePoint);
		lineLine(A, &right, &relativePoint);
	}
	else if (lineLine(A, &right, &entryPoint)) {
		lineLine(A, &up, &relativePoint);
		lineLine(A, &left, &relativePoint);
		lineLine(A, &down, &relativePoint);
	}
	colliding = (lineLine(A, &up) || lineLine(A, &down) || lineLine(A, &left) || lineLine(A, &right));
}
Collision::Collision(LineCollider* A, CircleCollider* B) {
	colliderA = A; colliderB = B;
	//line start or destination in circle
	if (pointCircle(A->x, A->y, B->x, B->y, B->radius) ||
		pointCircle(A->destX, A->destY, B->x, B->y, B->radius)) {
		colliding = true;
		entryPoint = sf::Vector2f(A->x, A->y);
		relativePoint = sf::Vector2f(B->x, B->y);
		return;
	}
	float lineLength = distance(A->x, A->y, A->destX, A->destY);
	float dot = (((B->x - A->x) * (A->destX - A->x)) + ((B->y - A->y) * (A->destY - A->y))) / pow(lineLength, 2);
	float closestX = A->x + (dot * (A->destX - A->x));
	float closestY = A->y + (dot * (A->destY - A->y));
	//is closest point on the line
	if (!linePoint(A->x, A->y, A->destX, A->destY, closestX, closestY)) {
		colliding = false;
		return;
	}
	//if closest point in circle
	if (distance(closestX, closestY, B->x, B->y) <= B->radius) colliding = true;
	entryPoint = sf::Vector2f(B->x, B->y);
	relativePoint = sf::Vector2f(closestX, closestY);

}

void Collision::getCollisionDetails(sf::Vector2f *result[2])
{
	sf::Vector2f details[2]{entryPoint, relativePoint};
	*result = details;
}


