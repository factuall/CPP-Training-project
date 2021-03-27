#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

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
	isTrigger = true;
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

	//REMOVE AFTER TESTING
	sf::Vertex angleLine[]{
		sf::Vertex(lastColliderPosition + sf::Vector2f(32,32)),
		sf::Vertex(lastColliderPosition + sf::Vector2f(32,32) + destVector)
	}; 
	angleLine[0].color = sf::Color::Green;
	angleLine[1].color = sf::Color::Green;
	window->draw(angleLine, 2, sf::Lines);
}

void Player::OnCollision(Collision collision) {
	//REMOVE AFTER TESTING
	///Saving it for rendering
	lastColliderPosition = sf::Vector2f(collision.colliderB->x, collision.colliderB->y);
	///Using 2px border until velocity is handled to avoid blocking 
	float safeDistance = 2.0;//px 
	destVector = collision.posDiffVector; 
	if (!((abs(destVector.x) > 64) || (abs(destVector.y) > 64))) {
		if (abs(destVector.x) > abs(destVector.y)) {
			//smaller first
			destVector.y *= (destVector.x / 64);
			destVector.x = 64 + safeDistance;
		}
		else {
			destVector.x *= (destVector.y / 64);
			destVector.y = 64 + safeDistance;
		}
		setPosition(lastColliderPosition.x + destVector.x, lastColliderPosition.y + destVector.y);
		velocity = sf::Vector2f();
	}

	
}