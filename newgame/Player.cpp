#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "base/BoxCollider.h"
#include "base/Collision.h"
#include "base/Collider.h"

Player::Player(int nX, int nY) {
	x = nX;
	y = nY;
	id = 0;
	isNull = false;
	collider = new BoxCollider(nX, nY, 32, 32);
	isTrigger = true;
};

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

	collider->x = x;
	collider->y = y;
	
	this->Move(velocityX, velocityY);
}

void Player::Render(sf::RenderWindow* window) {
	sprite.setPosition(pos);
	window->draw(sprite);
}

void Player::OnCollision(Collision collision) {}