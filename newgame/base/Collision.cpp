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

		int distX = B->x - tempX;
		int distY = B->y - tempY;
		float distance = sqrt((distX * distX) + (distY * distY));
		return (distance <= B->radius);

	}
	if (colliderA->type == Collider::ColliderType::CircleType && colliderB->type == Collider::ColliderType::CircleType) {
		CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		int distX = A->x - B->x;
		int distY = A->y - B->y;
		float distance = sqrt((distX * distX) + (distY * distY));
		return (distance <= (A->radius + B->radius));
	}
	if (colliderA->type == Collider::ColliderType::LineType && colliderB->type == Collider::ColliderType::CircleType) {
		LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		bool inside1 = (sqrt(((A->x - B->x) * (A->x - B->x)) + ((A->y - B->y) * (A->y - B->y))) <= B->radius);
		bool inside2 = (sqrt(((A->destX - B->x) * (A->destX - B->x)) + ((A->destY - B->y) * (A->destY - B->y))) <= B->radius);
		if (inside1 || inside2) return true;
		int distX = A->x - A->destX;
		int distY = A->y - A->destY;
		float len = sqrt((distX * distX) + (distY * distY));
		float dot = (((B->x - A->x) * (A->destX - A->x)) + ((B->y - A->y) * (A->destY - A->y))) / pow(len, 2);
		float closestX = A->x + (dot * (A->destX - A->x));
		float closestY = A->y + (dot * (A->destY - A->y));
		float dstX1 = closestX - A->x;
		float dstY1 = closestY - A->y;
		float dstX2 = closestX - A->destX;
		float dstY2 = closestY - A->destY;
		float d1 = sqrt((dstX1 * dstX1) + (dstY1 * dstY1));
		float d2 = sqrt((dstX2 * dstX2) + (dstY2 * dstY2));
		float buffer = 0.1; 
			if (!(d1 + d2 >= len - buffer && d1 + d2 <= len + buffer)) {
				return false;
			}
		float distX = closestX - B->x;
		float distY = closestY - B->y;
		float distance = sqrt((distX * distX) + (distY * distY));
		if (distance <= B->radius) {
			return true;
		}
	}
	return false;				
};

