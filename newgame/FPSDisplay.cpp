#include "FPSDisplay.h"

FPSDisplay::FPSDisplay()
{
	id = 0;
	isNull = false;
	collider->active = false;
	isTrigger = false;

	text = sf::Text();
	text.setCharacterSize(32);
	text.setString("fps");
	text.setFillColor(sf::Color::White);

}

void FPSDisplay::Render(sf::RenderWindow* window) {
	window->draw(text);
}