#include "LineCollider.h"
#include "Collider.h"
LineCollider::LineCollider(int nX, int nY, int nDestX, int nDestY) {
	pos.x = nX;
	pos.y = nY;
	destX = nDestX;
	destY = nDestY;
	dest.x = nDestX;
	dest.y = nDestY;
	type = Collider::ColliderType::LineType;
}