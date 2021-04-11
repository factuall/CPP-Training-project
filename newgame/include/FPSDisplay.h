#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"
class FPSDisplay :
	public fc::Object
{
public:
	FPSDisplay(sf::Text txt);
	FPSDisplay();
	void Render(sf::RenderWindow* window);
};
