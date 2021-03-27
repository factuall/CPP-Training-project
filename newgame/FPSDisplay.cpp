#include "FPSDisplay.h"

FPSDisplay::FPSDisplay()
{
	id = 0;
	isNull = false;
	collider->active = false;
	isTrigger = false;
	isVisible = true;
	text = sf::Text();
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