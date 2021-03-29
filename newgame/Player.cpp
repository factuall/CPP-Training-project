#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Player.h"
#include "base/BoxCollider.h"
#include "base/Collision.h"
#include "base/Collider.h"

using namespace sf;

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
	
	if (Keyboard::isKeyPressed(Keyboard::S) &&
		Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = 0;
	} //both keys - input cancelling
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		input.y = 1;
	} //down
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = -1;
	} //up

	if (Keyboard::isKeyPressed(Keyboard::D) &&
		Keyboard::isKeyPressed(Keyboard::A)) {
		input.x = 0;
	} //both keys - input cancelling
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		input.x = 1;
	} //right
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		input.x = -1;
	} //left
	
	float diagonalSlowDown = ((input.x != 0 && input.y != 0) ? 0.709f : 1.0f);
	velocity.x += (float)(((diagonalSlowDown * input.x * speed) - velocity.x) / walkSmoothness);
	if (abs(velocity.x) < 0.5) velocity.x = 0;
	velocity.y += (float)(((diagonalSlowDown * input.y * speed) - velocity.y) / walkSmoothness);
	if (abs(velocity.y) < 0.5) velocity.y = 0;

	normalizedVelocity = (operator*(Collision::normalize(velocity), (float)speed));

	this->Move(velocity);
	collider->pos = pos;


}

void Player::Render(RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);

	//REMOVE AFTER TESTING
	Vertex velocityLine[]{
	Vertex(pos + Vector2f(32,32)),
	Vertex(pos + Vector2f(32,32) + (operator*(normalizedVelocity, 4.0f)))
	};
	Vertex velocityLineCol[]{
	Vertex(pos + Vector2f(32,32)),
	Vertex(pos + Vector2f(32,32) + (operator*(forceBack, 4.0f)))
	};
	Vertex angleLine[]{
		Vertex(lastColliderPosition + Vector2f(32,32)),
		Vertex(lastColliderPosition + Vector2f(32,32) + destVector)
	}; 
	angleLine[0].color = Color::Green;
	angleLine[1].color = Color::Green;
	window->draw(angleLine, 2, Lines);
	window->draw(velocityLine, 2, Lines);
	window->draw(velocityLineCol, 2, Lines);
}

void Player::OnCollision(Collision collision) {

	//REMOVE AFTER TESTING
	///Saving it for rendering
	lastColliderPosition = collision.colliderB->pos;


	//if player inside
	//scale up vector to point outside
	//move player and then adjust his velocity
	destVector = collision.posDiffVector;
	int sqSize = collision.colliderB->squareSize;
	if (!((abs(destVector.x) > sqSize) || (abs(destVector.y) > sqSize))) {
		std::cout << velocity.x << " " << velocity.y << "\n";
		if (abs(destVector.x) > abs(destVector.y)) {
			destVector.y *= ((abs(destVector.x) + abs(velocity.x)) / sqSize);
			destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
		} else if(abs(destVector.x) < abs(destVector.y)){
			destVector.x *= ((abs(destVector.y) + abs(velocity.y)) / sqSize);
			destVector.y = (sqSize) * ((destVector.y < 0) ? -1 : 1);
		} else { //rare corner collision
			destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
			destVector.y = (sqSize) * ((destVector.x < 0) ? -1 : 1);
		}
		Move(operator+(collision.colliderB->pos, destVector));
		if (Collision::distance(Vector2f(), normalizedVelocity) != 0) {
			if (abs(destVector.x) > abs(destVector.y)) {
				velocity.x = 0;
			} else 
			if (abs(destVector.x) < abs(destVector.y)) {
				velocity.y = 0;
			} else { //rare corner collision
				velocity = Vector2f();
			}
		}
	}
}