#pragma once
#include "Collider.h"
class Collision {
public:
	Collider* colliderA;
	Collider* colliderB;
	bool areColliding();
private:
	float distance(int x, int y, int destX, int destY);
	bool pointCircle(int x, int y, int circleX, int circleY, int radius);
	bool linePoint(int x, int y, int destX, int destY, int pointX, int pointY);
};
