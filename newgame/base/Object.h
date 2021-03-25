#pragma once
#include <string>
#include <SFML/Graphics.hpp>
enum ObjectType {GameObject, TextObject};
class Object {
public: 
    int x, y, id;
    bool isNull = true;
    ObjectType type;
    Object(int nX, int nY, int nID);
    Object(int nX, int nY);
    Object();

    void Move(int mX, int mY);
    void setPosition(int mX, int mY);

    sf::Text text;
    sf::Sprite sprite;
private:

}; 
