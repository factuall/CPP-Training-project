#include "Door.h"
#include <iostream>

using namespace sf;
using namespace fc;
Door::Door() {
	isNull = true;
}
Door::Door(int nX, int nY, Texture* spriteSheet) {
	pos.x = nX;
	pos.y = nY;
	isNull = false;
	collider = new Collider(Vector2f(nX + 32, nY + 32), Vector2f(64, 64));
	collider->renderCollider = false;
	collider->charTag = 'd';
	isVisible = true;
	isTrigger = true;
	doorAnimation = new Animation(Vector2i(0, 672), Vector2i(64, 64), 6, 3);
	doorAnimation->loop = false;
	doorAnimation->playReverse = false;
	doorAnimation->Play();
	animator = SpriteController(spriteSheet, doorAnimation);
	animator.Update();
	sprite = animator.output;
}

void Door::Update() {
	if (active) {
		if (animator.currentAnimation->playReverse == open) {
			animator.currentAnimation->playReverse = !open;
			if (!animator.currentAnimation->isPlaying()) {
				animator.currentAnimation->Play();
			}
		}

		animator.Update();
		if (Keyboard::isKeyPressed(Keyboard::O)) {
			open = false;
		}
		if (Keyboard::isKeyPressed(Keyboard::P)) {
			open = true;
		}
	}
}

void Door::ManagedRender(RenderWindow* window) {
	sprite = animator.output;
	sprite.setScale(spriteScale());
	sprite.setOrigin(32, 32);
	sprite.setRotation(angle);
	sprite.setPosition(pos + Vector2f(64, 64));
	window->draw(sprite);
	//collider->RenderCollider(window);
}

void Door::OnCollision(Collision collision) {
	if (collision.colliderB->charTag == 'p') {
		entered = true;
	}
}