#include "Door.h"
#include <iostream>

using namespace sf;
using namespace fc;
Door::Door() {
	isNull = true;
}
Door::Door(int nX, int nY, int offX, int offY, Texture* spriteSheet) {
	pos.x = nX;
	pos.y = nY;
	this->offX = offX;
	this->offY = offY;
	isNull = false;
	collider = new Collider(Vector2f(nX + 32 + offX, nY + 32 + offY), Vector2f(64, 64), ColliderType::CircleType);
	collider->renderCollider = false;
	collider->charTag = 'd';
	isVisible = true;
	isTrigger = true;
	doorAnimation = new Animation(Vector2i(0, 672), Vector2i(64, 64), 6, 3);
	doorAnimation->loop = false;
	doorAnimation->playReverse = false;
	doorAnimation->Stop();
	doorAnimation->setCurrentFrame(doorAnimation->getLength() - 1);

	animator = SpriteController(spriteSheet, doorAnimation);
	animator.Update();

	sprite = animator.output;
}

void Door::Update() {
	if (active) {
		if (open){
			collider->charTag = 'd';
			collider->pos.x = pos.x + 32 + offX;
			collider->pos.y = pos.y + 32 + offY;
		}	
		else {
			collider->charTag = 'D';
			collider->pos.x = pos.x + 32 + (offX / 2);
			collider->pos.y = pos.y + 32 + (offY / 2);
		}
			
		if (animator.currentAnimation->playReverse == open) {
			animator.currentAnimation->playReverse = !open;
			if (!animator.currentAnimation->isPlaying()) {
				animator.currentAnimation->Play();
			}
		}
		animator.Update();
	}
}

void Door::ManagedRender(RenderWindow* window) {
	sprite = animator.output;
	sprite.setScale(spriteScale());
	sprite.setOrigin(32, 32);
	sprite.setRotation(angle);
	sprite.setPosition(pos + Vector2f(64, 64));
	window->draw(sprite);
	if(collider->renderCollider)
		collider->RenderCollider(window);
}

void Door::OnCollision(Collision collision) {
	if (collision.colliderB->charTag == 'p' && this->collider->charTag == 'd') {
		entered = true;
	}
}