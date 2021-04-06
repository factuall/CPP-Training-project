#include "Door.h"

using namespace sf;
using namespace fc;
Door::Door() {
	isNull = true;
}
Door::Door(int nX, int nY, Texture* txt) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(nX, nY), Vector2f(64, 64), Vector2f(16, 26));
	isVisible = true;
	isTrigger = false;
	doorAnimation = Animation(Vector2i(0, 672),Vector2i(64,64),6,4);
	doorAnimation.loop = false;
	doorAnimation.playReverse = true;
	doorAnimation.Play();
	animator = SpriteController(txt, &doorAnimation);
	animator.Update();
	sprite = animator.output;
}

void Door::Update() {
	collider->pos = pos;
	animator.Update();
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		doorAnimation.playReverse = false;
		doorAnimation.Play();
	}
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		doorAnimation.playReverse = true;
		doorAnimation.Play();
	}

}

void Door::Render(RenderWindow* window) {
	sprite = animator.output;
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);

}
