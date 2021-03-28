#include "CircleCollider.h"
CircleCollider::CircleCollider(int nX, int nY, int nRadius) {
	pos.x = nX;
	pos.y = nY;
	radius = nRadius;
	type = Collider::ColliderType::CircleType;
}