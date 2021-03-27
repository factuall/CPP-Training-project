#include <SFML/Graphics.hpp>

#include "Object.h"
#include "CircleCollider.h"
#include "Collision.h"

Object::Object(int nX, int nY) {
    x = nX;
    y = nY;
    pos = sf::Vector2f(nX, nY);
    id = 0;
    isNull = false;

}

Object::Object() {
    x = 0;
    y = 0;
    pos = sf::Vector2f(0, 0);
    id = 0;
    isNull = true;
}

void Object::Move(int mX, int mY) {
    x += mX;
    y += mY;
    pos.x += mX;
    pos.y += mY;
}

void Object::setPosition(int mX, int mY) {
    x = mX;
    y = mY;
    pos = sf::Vector2f(mX, mY);
}

void Object::Update() {
    if (collider->active) {
        collider->x = x; collider->y = y;
    }
}

void Object::Render(sf::RenderWindow* window){}

void Object::OnCollision(Collision collision){}

Collider* Object::getCollider() {
    return collider;
}