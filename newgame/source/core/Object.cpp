

#include "Object.h"
#include <cmath>

namespace fc {
    Object::Object(int nX, int nY) {
        pos = sf::Vector2f(nX, nY);
        id = 0;
        isNull = false;
    }

    Object::Object() {
        pos = sf::Vector2f();
        id = 0;
        isNull = true;
    }

    void Object::Move(sf::Vector2f mPos) {
        pos.x += mPos.x;
        pos.y += mPos.y;
    }

    void Object::setPosition(sf::Vector2f xPos) {
        pos.x = round(xPos.x);
        pos.y = round(xPos.y);
        collider->pos = pos;
    }

    void Object::Update() {
        if (collider->active) {
            collider->pos = pos;
        }
    }

    void Object::Render(sf::RenderWindow* window) {
        if (isVisible) {
            sprite.setScale(spriteScale());
            sprite.setPosition(pos);
            window->draw(sprite);
        }
        if (collider->renderCollider) {
            collider->RenderCollider(window);
        }
    }

    void Object::OnCollision(Collision collision) {}

    Collider* Object::getCollider() {
        return collider;
    }

    sf::Vector2f Object::spriteScale() {
        return sf::Vector2f(2, 2);
    }
}
