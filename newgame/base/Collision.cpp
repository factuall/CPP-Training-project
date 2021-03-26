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

bool Collision::areColliding() {
	if (colliderA->type == Collider::ColliderType::BoxType && colliderB->type == Collider::ColliderType::BoxType) {
		BoxCollider* A = dynamic_cast<BoxCollider*>(colliderA),
			* B = dynamic_cast<BoxCollider*>(colliderB);
		return (A->x < B->x + B->width &&
			A->x + A->width > B->x &&
			A->y < B->y + B->height &&
			A->y + A->height > B->y);
	}
	if (colliderA->type == Collider::ColliderType::BoxType && colliderB->type == Collider::ColliderType::CircleType ||
		colliderA->type == Collider::ColliderType::CircleType && colliderB->type == Collider::ColliderType::BoxType) {
		BoxCollider* A;
		CircleCollider* B;
		if (colliderA->type == Collider::ColliderType::BoxType && colliderB->type == Collider::ColliderType::CircleType) {
			A = dynamic_cast<BoxCollider*>(colliderA);
			B = dynamic_cast<CircleCollider*>(colliderB);
		} else if(colliderA->type == Collider::ColliderType::CircleType && colliderB->type == Collider::ColliderType::BoxType) {
			A = dynamic_cast<BoxCollider*>(colliderB);
			B = dynamic_cast<CircleCollider*>(colliderA);
		}

		int tempX = B->x;
		int tempY = B->y;
		if (B->x < A->x)         tempX = A->x;      // test left edge
		else if (B->x > A->x + A->width) tempX = A->x + A->width;   // right edge
		if (B->y < A->y)         tempY = A->y;      // top edge
		else if (B->y > A->y + A->height) tempY = A->y + A->height;   // bottom edge

		//is distance from closest edge smaller than circle radius
		return (distance(B->x, B->y, tempX, tempY) <= B->radius);

	}
	if (colliderA->type == Collider::ColliderType::CircleType && colliderB->type == Collider::ColliderType::CircleType) {
		CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		//is distance between circles smaller than sum of their radius
		return (distance(A->x, A->y, B->x, B->y) <= (A->radius + B->radius));
	}
	if (colliderA->type == Collider::ColliderType::LineType && colliderB->type == Collider::ColliderType::CircleType) {
		LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		//line start or destination in circle
		if (pointCircle(A->x, A->y, B->x, B->y, B->radius) ||
			pointCircle(A->destX, A->destY, B->x, B->y, B->radius)) return true;
		float lineLength = distance(A->x, A->y, A->destX, A->destY);
		float dot = (((B->x - A->x) * (A->destX - A->x)) + ((B->y - A->y) * (A->destY - A->y))) / pow(lineLength, 2);
		float closestX = A->x + (dot * (A->destX - A->x));
		float closestY = A->y + (dot * (A->destY - A->y));
		//is closest point on the line
		if (!linePoint(A->x, A->y, A->destX, A->destY, closestX, closestY)) return false;
		//if closest point in circle
		if (distance(closestX, closestY, B->x, B->y) <= B->radius) return true;
	}
	return false;				
};

