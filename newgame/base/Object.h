#pragma once
#include <string>
#include <SFML/Graphics.hpp>
enum ObjectType {GameObject, TextObject};
class Object {
public: 
    int x, y, id;
    int sizeX = 64, sizeY = 64;
    bool isNull = true, isVisible = true, isCollider = false;
    ObjectType type;

    Object(int nX, int nY, int nID);
    Object(int nX, int nY);
    Object();

    void Move(int mX, int mY);
    void setPosition(int mX, int mY);

    virtual void Update();
    virtual void OnColision(Object *collider);

    sf::Text text;
    sf::Sprite sprite;
private:

}; 
