#include "LineCollider.h"
LineCollider::LineCollider(int nX, int nY, int nDestX, int nDestY) {
	x = nX;
	y = nY;
	destX = nDestX;
	destY = nDestY;
	type = LineType;
}