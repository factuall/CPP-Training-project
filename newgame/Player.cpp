#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Player.h"
#include "base/BoxCollider.h"
#include "base/Collision.h"
#include "base/Collider.h"

Player::Player(int nX, int nY) {
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

	collider->pos = pos;
	
	this->Move(velocity);
}

void Player::Render(sf::RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);

	//REMOVE AFTER TESTING
	sf::Vertex velocityLine[]{
	sf::Vertex(pos + sf::Vector2f(32,32)),
	sf::Vertex(pos + sf::Vector2f(32,32) + sf::Vector2f(velocity.x * 6, velocity.y * 6))
	};
	sf::Vertex angleLine[]{
		sf::Vertex(lastColliderPosition + sf::Vector2f(32,32)),
		sf::Vertex(lastColliderPosition + sf::Vector2f(32,32) + destVector)
	}; 
	angleLine[0].color = sf::Color::Green;
	angleLine[1].color = sf::Color::Green;
	window->draw(angleLine, 2, sf::Lines);
	window->draw(velocityLine, 2, sf::Lines);
}

void Player::OnCollision(Collision collision) {
	//REMOVE AFTER TESTING
	///Saving it for rendering
	lastColliderPosition = collision.colliderB->pos;
	///Using 1px border until velocity is handled to avoid blocking 
	float safeDistance = 1.0;//px 
	destVector = collision.posDiffVector; 
	sf::Vector2f before = destVector;
	int sqSize = collision.colliderB->squareSize;
	//if inside
	if (!((abs(destVector.x) > sqSize) || (abs(destVector.y) > sqSize))) {
		//scale vector up
		if (abs(destVector.x) > abs(destVector.y)) {
			//smaller first
			destVector.y *= (abs(destVector.x) / sqSize);
			destVector.x = (sqSize + safeDistance) * ((destVector.x < 0) ? -1 : 1);
		}
		else {
			destVector.x *= (abs(destVector.y) / sqSize);
			destVector.y = (sqSize + safeDistance) * ((destVector.y < 0) ? -1 : 1);
		}
		setPosition(sf::operator+(collision.colliderB->pos, destVector));
		velocity = sf::Vector2f();
	}

	
}