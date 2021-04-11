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
	isVisible = false;
	isTrigger = true;
	collider->renderCollider = false;
	///
	bodyAnimationV = Animation(Vector2i(0, 128), Vector2i(32, 32), 8, 4);
	bodyAnimationV.loop = true;
	bodyAnimationV.playReverse = false;
	bodyAnimationV.Play();
	bodyAnimationH = Animation(Vector2i(0, 160), Vector2i(32, 32), 8, 4);
	bodyAnimationH.loop = true;
	bodyAnimationH.playReverse = false;
	bodyAnimationH.Play();
	bodyAnimator = SpriteController(spriteSheet, &bodyAnimationV);
	bodyAnimator.Update();
	sprite = bodyAnimator.output;
	headStates = Animation(Vector2i(0, 192), Vector2i(32, 32), 4,999999);
	headStates.Stop();
	headAnimator = SpriteController(spriteSheet, &headStates);
};

void Player::Update() {
	input.x = 0; input.y = 0;
	bodyAnimationV.Pause();
	bodyAnimationH.Pause();
	bodyAnimator.Update();
	if (Keyboard::isKeyPressed(Keyboard::S) &&
		Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = 0;
	} //both keys - input cancelling
	else if (Keyboard::isKeyPressed(Keyboard::S)) {
		input.y = 1;
		bodyAnimationV.Resume();
		headStates.setCurrentFrame(0);
	} //down
	else if (Keyboard::isKeyPressed(Keyboard::W)) {
		input.y = -1;
		bodyAnimationV.Resume();
		headStates.setCurrentFrame(2);
	} //up

	if (Keyboard::isKeyPressed(Keyboard::D) &&
		Keyboard::isKeyPressed(Keyboard::A)) {
		input.x = 0;
	} //both keys - input cancelling
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		input.x = 1;
		bodyAnimationH.Resume();
		headStates.setCurrentFrame(1);
	} //right
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		input.x = -1;
		bodyAnimationH.Resume();
		headStates.setCurrentFrame(3);
	} //left


	if (input.y == 0) bodyAnimationV.Stop();
	else bodyAnimator.currentAnimation = &bodyAnimationV;
	if (input.x == 0) bodyAnimationH.Stop();
	else bodyAnimator.currentAnimation = &bodyAnimationH;
	if (input.x == 0 && input.y == 0) {

		bodyAnimator.currentAnimation = &bodyAnimationV;
	}
	bodyAnimator.Update();
	headAnimator.Update();

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
	sprite = bodyAnimator.output;
	sprite.setScale((input.x < 0) ? Vector2f(-2.f, 2.f) : spriteScale());
	sprite.setPosition(pos + ((input.x < 0) ? Vector2f(64.f, 0) : Vector2f()) + Vector2f(0, 14.f));
	
	headSprite = headAnimator.output;
	headSprite.setPosition(pos + Vector2f(0, -7.f));
	headSprite.setScale(spriteScale());
	window->draw(sprite);
	window->draw(headSprite);
	if (collider->renderCollider) {
		collider->RenderCollider(window);
	}
}

void Player::OnCollision(fc::Collision collision) {
	if (collision.colliderB->charTag == 'd') return;
	collision.adaptCollider(velocity);
	setPosition(collision.adaptedPosition);
	velocity = collision.adaptedVelocity;
}