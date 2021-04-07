#include "Player.h"
#include <iostream>

using namespace sf;
using namespace fc;
Player::Player(int nX, int nY, Texture* spriteSheet) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(nX, nY), Vector2f(64, 64), ColliderType::CircleType);
	collider->charTag = 'p';
	isVisible = true;
	isTrigger = true;
	collider->renderCollider = true;
	///
	bodyAnimation = Animation(Vector2i(0, 128), Vector2i(32, 32), 8, 4);
	bodyAnimation.loop = true;
	bodyAnimation.playReverse = false;
	bodyAnimation.Play();
	animator = SpriteController(spriteSheet, &bodyAnimation);
	animator.Update();
	sprite = animator.output;
	headSprite = Sprite(*spriteSheet, IntRect(192, 0, 32, 32));
};

void Player::Update() {
	input.x = 0; input.y = 0;
	bodyAnimation.Pause();
	animator.Update();
	if (Keyboard::isKeyPressed(Keyboard::S) &&
		Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = 0;
	} //both keys - input cancelling
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		input.y = 1;
		bodyAnimation.Resume();
	} //down
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = -1;
		bodyAnimation.Resume();
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
	if (input.y == 0) bodyAnimation.Stop();
	animator.Update();

	float diagonalSlowDown = ((input.x != 0 && input.y != 0) ? 0.709f : 1.0f);
	velocity.x += (float)(((diagonalSlowDown * input.x * speed) - velocity.x) / walkSmoothness);
	if (abs(velocity.x) < 0.5) velocity.x = 0;
	velocity.y += (float)(((diagonalSlowDown * input.y * speed) - velocity.y) / walkSmoothness);
	if (abs(velocity.y) < 0.5) velocity.y = 0;

	//normalizedVelocity = (operator*(normalize(velocity), (float)speed));

	this->Move(velocity);
	collider->pos = pos;
}

void Player::ManagedRender(RenderWindow* window) {
	sprite = animator.output;
	sprite.setPosition(pos + Vector2f(0, 14.0f));
	sprite.setScale(spriteScale());

	headSprite.setPosition(pos + Vector2f(0, -12.0f));
	headSprite.setScale(spriteScale());
	window->draw(sprite);
	window->draw(headSprite);
	if (collider->renderCollider) {
		//collider->RenderCollider(window);
	}
}

void Player::OnCollision(fc::Collision collision) {
	if (collision.colliderB->charTag == 'd') return;
	collision.adaptCollider(velocity);
	setPosition(collision.adaptedPosition);
	velocity = collision.adaptedVelocity;
}