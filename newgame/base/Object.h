#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
class Object {
public: 
    int x, y, id;
    sf::Vector2f pos;
    int sizeX = 64, sizeY = 64;
    bool isNull = true, isVisible = false;

    Object(int nX, int nY);
    Object();

    void Move(float mX, float mY);
    void setPosition(int mX, int mY);

    virtual void Update();
    virtual void Render(sf::RenderWindow* window);
    virtual void OnCollision(Collision collision);

    sf::Text text;
    sf::Sprite sprite;

    Collider *collider = new Collider();
    Collider *getCollider();
    bool isTrigger = false;
    sf::Vector2f spriteScale();
private:
}; 
