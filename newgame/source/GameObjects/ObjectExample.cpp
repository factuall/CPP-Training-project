#include "ObjectExample.h"

using namespace sf;
using namespace fc;
ObjectExample::ObjectExample(int nX, int nY) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(nX, nY), Vector2f(4, 4));
	isVisible = false;
	isTrigger = false;
};

void ObjectExample::Update() {
	collider->pos = pos;
}

void ObjectExample::Render(RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);
}

void ObjectExample::OnCollision(fc::Collision collision) {
}