#pragma once

#include <SFML/System.hpp>

class Collider {
public:
	enum class ColliderType { BoxType, CircleType, LineType, PointType };
	sf::Vector2f pos = sf::Vector2f();
	int squareSize;
	bool active = false;
	ColliderType type = Collider::ColliderType::PointType;
	virtual ~Collider();
};
