#include <tgmath.h>
#include <iostream>

#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"



bool Collision::linePoint(sf::Vector2f linePos, sf::Vector2f lineDest, sf::Vector2f point) {
	float dist = distance(point, linePos);
	float distDest = distance(point, lineDest);
	float lineLength = distance(linePos, lineDest);
	float buffer = 0.1;
	return (dist + distDest >= lineLength - buffer && dist + distDest <= lineLength + buffer);
}

bool Collision::pointCircle(sf::Vector2f point, sf::Vector2f circle, int radius) {
	return (distance(point, circle) <= radius);
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
	return (distance(A->pos, B->pos) <= (A->radius + B->radius));
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
	A->pos.x = round(A->pos.x);
	A->pos.y = round(A->pos.y);
	B->pos.x = round(B->pos.x);
	B->pos.y = round(B->pos.y);

	sf::Vector2f temp = B->pos;
	if (B->pos.x < A->pos.x)         temp.x = A->pos.x;						// test left edge
	else if (B->pos.x > A->pos.x + A->width) temp.x = A->pos.x + A->width;   // right edge
	if (B->pos.y < A->pos.y)         temp.y = A->pos.y;						// top edge
	else if (B->pos.y > A->pos.y + A->height) temp.y = A->pos.y + A->height; // bottom edge
	//is distance from closest edge smaller than circle radius
	entryPos = sf::Vector2f(); posDiffVector = sf::Vector2f();
	entryPos.x = A->pos.x; entryPos.y = A->pos.y;
	posDiffVector.x = B->pos.x; posDiffVector.y = B->pos.y;
	return (distance(B->pos, temp) <= B->radius);

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
	if (pointCircle(A->pos, B->pos, B->radius) ||
		pointCircle(A->dest, B->pos, B->radius)) {
		entryPos = sf::Vector2f(A->pos.x, A->pos.y);
		posDiffVector = sf::Vector2f(B->pos.x, B->pos.y);
		return true;
	}
	float lineLength = distance(A->pos, A->dest);
	float dot = (((B->pos.x - A->pos.x) * (A->dest.x - A->pos.x)) + ((B->pos.y - A->pos.y) * (A->dest.y - A->pos.y))) / pow(lineLength, 2);
	sf::Vector2f closest = sf::Vector2f(
		A->pos.x + (dot * (A->dest.x - A->pos.x)),
		A->pos.y + (dot * (A->dest.y - A->pos.y))
	);
	//is closest point on the line
	if (!linePoint(A->pos, A->dest, closest)) {
		
		return false;
	}
	//if closest point in circle
	entryPos = sf::Vector2f(B->pos.x, B->pos.y);
	posDiffVector = closest;
	if (distance(closest, B->pos) <= B->radius) return  true;


}

void Collision::getCollisionDetails(sf::Vector2f *result[2])
{
	sf::Vector2f details[2]{entryPos, posDiffVector};
	*result = details;
}

float Collision::distance(sf::Vector2f A, sf::Vector2f B) {
	return sqrt(((A.x - B.x) * (A.x - B.x)) + ((A.y - B.y) * (A.y - B.y)));
}

sf::Vector2f Collision::normalize(sf::Vector2f source) {
	float length = distance(sf::Vector2f(), source);
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}