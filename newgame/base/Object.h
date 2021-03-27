#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
enum ObjectType {GameObject, TextObject, ShapeObject};
class Object {
public: 
    int x, y, id;
    int sizeX = 64, sizeY = 64;
    bool isNull = true, isVisible = true;
    ObjectType type = GameObject;

    Object(int nX, int nY);
    Object();

    void Move(int mX, int mY);
    void setPosition(int mX, int mY);

    virtual void Update();
    virtual void OnCollision(Collision collision);

    sf::Text text;
    sf::Sprite sprite;
    sf::RectangleShape visualShape;

    Collider *collider = new Collider();
    Collider *getCollider();
    bool isTrigger = false;
private:

}; 
