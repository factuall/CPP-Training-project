#include "Object.h"
#include "CircleCollider.h"
#include "Collision.h"


Object::Object(int nX, int nY, int nID) {
    x = nX;
    y = nY;
    id = nID;
    isNull = false;
}

Object::Object(int nX, int nY) {
    x = nX;
    y = nY;
    id = 0;
    isNull = false;
    collider = new CircleCollider(nX, nY, 64);
    isCollisionListener = false;
}

Object::Object() {
    x = 0;
    y = 0;
    id = 0;
    isNull = true;
    
}

void Object::Move(int mX, int mY) {
    x += mX;
    y += mY;
}

void Object::setPosition(int mX, int mY) {
    x = mX;
    y = mY;
}

void Object::Update() {
}

void Object::OnCollision(Collision collision) {
}


Collider* Object::getCollider() {
    return collider;
}