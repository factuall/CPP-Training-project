#include "Collider.h"
namespace fc {
	Collider::Collider(Vector2f pos, Vector2f size, ColliderType type) {
		this->pos = pos;
		this->size = size;
		this->type = type;
		this->squareSize = size.x;
		active = true;
	}
	Collider::Collider(Vector2f pos, Vector2f size) {
		this->pos = pos;
		this->size = size;
		this->type = ColliderType::BoxType;
		this->squareSize = size.x;
		active = true;
	}
}