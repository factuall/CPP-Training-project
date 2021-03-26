#pragma once
#include "Collider.h"
class BoxCollider : public Collider {
public:
	int width, height;
	BoxCollider(int nX, int nY, int nWidth, int nHeight);
};