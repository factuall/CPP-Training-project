#pragma once
#include "Collider.h"
class LineCollider : public Collider {
public:
	int destX, destY;
	LineCollider(int nX, int nY, int nDestX, int nDestY);
};