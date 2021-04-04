#include "Player.h"

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
	collision.adaptCollider(velocity);
	setPosition(collision.adaptedPosition);
	velocity = collision.adaptedVelocity;
	
}