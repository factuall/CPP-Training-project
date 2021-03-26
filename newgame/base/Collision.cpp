#include <tgmath.h>

#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

bool Collision::areColliding() {
	if (colliderA->type == BoxType && colliderB->type == BoxType) {
		BoxCollider* A = dynamic_cast<BoxCollider*>(colliderA),
			* B = dynamic_cast<BoxCollider*>(colliderB);
		return (A->x < B->x + B->width &&
			A->x + A->width > B->x &&
			A->y < B->y + B->height &&
			A->y + A->height > B->y);
	}
	if (colliderA->type == BoxType && colliderB->type == CircleType) {
		BoxCollider* A = dynamic_cast<BoxCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
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
	if (colliderA->type == CircleType && colliderB->type == BoxType) {
		CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
		BoxCollider* B = dynamic_cast<BoxCollider*>(colliderB);
		int tempX = A->x;
		int tempY = A->y;
		if (A->x < B->x)         tempX = B->x;      // test left edge
		else if (A->x > B->x + B->width) tempX = B->x + B->width;   // right edge
		if (A->y < B->y)         tempY = B->y;      // top edge
		else if (A->y > B->y + B->height) tempY = B->y + B->height;   // bottom edge

		int distX = A->x - tempX;
		int distY = A->y - tempY;
		float distance = sqrt((distX * distX) + (distY * distY));
		return (distance <= A->radius);

	}
	if (colliderA->type == CircleType && colliderB->type == CircleType) {
		CircleCollider* A = dynamic_cast<CircleCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		int distX = A->x - B->x;
		int distY = A->y - B->y;
		float distance = sqrt((distX * distX) + (distY * distY));
		return (distance <= (A->radius + B->radius));
	}
	return false;				
};

