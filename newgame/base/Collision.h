#pragma once
#include "Collider.h"
class Collision {
public:
	Collider* colliderA;
	Collider* colliderB;
	bool areColliding();
private:
	bool linePoint(int x, int y, int destX, int destY, int pointX, int pointY);
	float distance(int x, int y, int destX, int destY);
};
