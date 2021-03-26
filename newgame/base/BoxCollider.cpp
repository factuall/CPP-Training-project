#include "BoxCollider.h"
BoxCollider::BoxCollider(int nX, int nY, int nWidth, int nHeight){
	x = nX;
	y = nY;
	width = nWidth;
	height = nHeight;
	type = Collider::ColliderType::BoxType;
}