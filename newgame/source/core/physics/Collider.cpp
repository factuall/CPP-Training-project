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
	Collider::Collider(Vector2f pos, Vector2f size, Vector2f offset) {
		this->pos = pos;
		this->size = size;
		this->type = ColliderType::BoxType;
		this->offset = offset;
		this->squareSize = size.x;
		active = true;
	}
	void Collider::RenderCollider(sf::RenderWindow* window){
		if (this->type == ColliderType::BoxType) {
			sf::RectangleShape shape(this->size);
			shape.setPosition(this->pos);
			shape.setFillColor(sf::Color(155, 0, 255, 100));
			window->draw(shape);
		}
		else {
			sf::CircleShape shape(this->size.x / 2);
			shape.setPosition(this->pos);
			shape.setFillColor(sf::Color(255, 0, 155, 100));
			window->draw(shape);
		}
	}
}