#pragma once
#include "Collider.h"
class LineCollider : public Collider {
public:
	int destX, destY;
	sf::Vector2f dest = sf::Vector2f();
	LineCollider(int nX, int nY, int nDestX, int nDestY);
};