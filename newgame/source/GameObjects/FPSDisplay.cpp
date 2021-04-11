#include "FPSDisplay.h"
#include "Collider.h"
FPSDisplay::FPSDisplay(sf::Text txt)
{
	id = 0;
	isNull = false;
	collider = new fc::Collider(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	collider->active = false;
	isTrigger = false;
	isVisible = true;
	text = txt;
	text.setCharacterSize(32);
	text.setString("fps");
	text.setFillColor(sf::Color::White);
}


void FPSDisplay::Render(sf::RenderWindow* window) {
	if (isVisible) {
		sprite.setScale(spriteScale());
		pos.x = 0;
		pos.y = 0;
		sprite.setPosition(pos);
		window->draw(sprite);
	}
	window->draw(text);
}