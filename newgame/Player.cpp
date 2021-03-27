#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "base/BoxCollider.h"
#include "base/Collision.h"
#include "base/Collider.h"

Player::Player(int nX, int nY) {
	x = nX;
	y = nY;
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new BoxCollider(nX, nY, 64, 64);
	isVisible = true;
};

void Player::Update() {
	
	input.x = 0; input.y = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		input.y = 0;
	} //both keys - input cancelling
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		input.y = 1;
	} //down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		input.y = -1;
	} //up

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		input.x = 0;
	} //both keys - input cancelling
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		input.x = 1;
	} //right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		input.x = -1;
	} //left

	
	velocity.x += (float)(((input.x * speed) - velocity.x) / walkSmoothness);
	velocity.y += (float)(((input.y * speed) - velocity.y) / walkSmoothness);

	collider->x = x;
	collider->y = y;
	
	this->Move(velocity.x, velocity.y);
}

void Player::Render(sf::RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);
}

void Player::OnCollision(Collision collision) {}