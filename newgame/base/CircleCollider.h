#pragma once
#include "Collider.h"
class CircleCollider : public Collider {
public:
	int radius;
	CircleCollider(int nX, int nY, int nRadius);
};