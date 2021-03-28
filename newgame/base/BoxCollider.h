#pragma once
#include "Collider.h"
class BoxCollider : public Collider {
public:
	int width, height;
	sf::Vector2f size = sf::Vector2f();
	BoxCollider(int nX, int nY, int nWidth, int nHeight);
};