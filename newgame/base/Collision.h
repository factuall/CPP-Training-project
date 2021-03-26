#pragma once
#include "Collider.h"
class Collision {
public:
	Collider* colliderA;
	Collider* colliderB;
	bool areColliding();
};
