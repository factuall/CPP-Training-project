#include <iostream>
#include <SFML/Main.hpp>

#include "Player.h"


Player::Player(int nX, int nY) {
	x = nX;
	y = nY;
	id = 0;
	isNull = false;
	
}

void Player::Update() {
	inputX = 0; inputY = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		inputY = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		inputY = -1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		inputX = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		inputX = -1;
	}

	velocityX += (float)(((inputX * speed) - velocityX) / walkSmoothness);
	velocityY += (float)(((inputY * speed) - velocityY) / walkSmoothness);

	this->Move(velocityX, velocityY);
}

void Player::OnCollision(Object *collider) {

}