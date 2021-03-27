#include <iostream>
#include <SFML/Main.hpp>

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

void Player::OnCollision(Collision collision) {
	BoxCollider* pCollider = dynamic_cast<BoxCollider*>(collision.colliderA);
	pl = sf::Vector2f(pCollider->x + (pCollider->width / 2), pCollider->y + (pCollider->height / 2));
	cl = collision.entryPoint + sf::Vector2f(collision.relativePoint.x/2, collision.relativePoint.y/2) - pl;
	cl.x = cl.x * -1; 
	cl.y = cl.y * -1;
	cl += pl;
	if (collision.colliding) {
		velocityX += kolizjaaa.x/8;
		velocityY += kolizjaaa.y/8;
	}
	if (x > (collision.entryPoint.x - pCollider->width) && x < collision.entryPoint.x + collision.relativePoint.x) {
		
	}

	
}