#include "CircleCollider.h"
CircleCollider::CircleCollider(int nX, int nY, int nRadius) {
	x = nX;
	y = nY;
	radius = nRadius;
	type = Collider::ColliderType::CircleType;
}