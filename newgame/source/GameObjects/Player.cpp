#include "Player.h"

#include <iostream>

#include <cmath>

using namespace sf;
using namespace fc;
Player::Player(int nX, int nY) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(nX, nY), Vector2f(64, 64), fc::ColliderType::CircleType);
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

	//normalizedVelocity = (operator*(normalize(velocity), (float)speed));

	this->Move(velocity);
	collider->pos = pos;


}

void Player::Render(RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);
}

void Player::OnCollision(fc::Collision collision) {
	/*
	if (collision.colliderB->type == fc::ColliderType::BoxType) {
		//REMOVE AFTER TESTING
	///Saving it for rendering
		lastColliderPosition = collision.colliderB->pos;


		//if player inside
		//scale up vector to point outside
		//move player and then adjust his velocity

		destVector = collision.diffVector;
		int sqSize = collision.colliderB->squareSize;
		if (!((abs(destVector.x) > sqSize) || (abs(destVector.y) > sqSize))) {
			if (abs(destVector.x) > abs(destVector.y)) {
				destVector.y *= ((abs(destVector.x) + abs(velocity.x)) / sqSize);
				destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
			}
			else if (abs(destVector.x) < abs(destVector.y)) {
				destVector.x *= ((abs(destVector.y) + abs(velocity.y)) / sqSize);
				destVector.y = (sqSize) * ((destVector.y < 0) ? -1 : 1);
			}
			else { //rare corner collision
				destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
				destVector.y = (sqSize) * ((destVector.x < 0) ? -1 : 1);
			}
			setPosition(operator+(collision.colliderB->pos, destVector));
			if (collision.distance(Vector2f(), (operator*(velocity,(float)speed))) != 0) {
				if (abs(destVector.x) > abs(destVector.y)) {
					velocity.x = 0;
				}
				else
					if (abs(destVector.x) < abs(destVector.y)) {
						velocity.y = 0;
					}
					else { //rare corner collision
						velocity = Vector2f();
					}
			}
		}
	}
	if (collision.colliderB->type == fc::ColliderType::CircleType) {
		lastColliderPosition = collision.colliderB->pos;
		float speed;

		//if player inside
		//scale up vector to point outside
		//move player and then adjust his velocity

		destVector = collision.diffVector;
		int sqSize = collision.colliderB->squareSize;
		if (collision.distance(collision.colliderA->pos, collision.colliderB->pos) < collision.colliderA->squareSize + collision.colliderB->squareSize) {
			while (collision.distance(destVector + collision.colliderA->pos, collision.colliderB->pos) < collision.colliderA->squareSize + collision.colliderB->squareSize) {
				destVector.x = destVector.x * 1.01f;
				destVector.y = destVector.y * 1.01f;
			}

			setPosition(operator+(collision.colliderB->pos, destVector));
			
			if (abs(velocity.x) > abs(velocity.y)) {
				velocity.y = abs(velocity.x) * ((destVector.y < 0) ? -1 : 1);
				velocity.x = abs((collision.normalize(velocity).x) + (collision.normalize(destVector).x)) * velocity.x;
			}
			else if (abs(velocity.x) < abs(velocity.y)) {
				velocity.x = abs(velocity.y) * ((destVector.x < 0) ? -1 : 1);
				velocity.y = abs((collision.normalize(velocity).y) + (collision.normalize(destVector).y)) * velocity.y;
			}
			else {

			}
			

			
		}
	}*/
	collision.adaptCollider(velocity);
	setPosition(collision.adaptedPosition);
	velocity = collision.adaptedVelocity;
}