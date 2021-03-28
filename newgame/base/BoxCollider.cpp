#include "BoxCollider.h"
BoxCollider::BoxCollider(int nX, int nY, int nWidth, int nHeight){
	pos.x = nX;
	pos.y = nY;
	width = nWidth;
	height = nHeight;
	size.x = nWidth;
	size.y = nHeight;
	squareSize = nWidth;
	type = Collider::ColliderType::BoxType;
	active = true;
}