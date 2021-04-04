#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"

using namespace sf;
using namespace fc;
class GameFloor :
    public Object
{
public:
    GameFloor(sf::Text txt);
    void Start();
    void Update();
    void Render(RenderWindow* window);
    void OnCollision(fc::Collision collision);
    char room[20][20];
    Vector2i orderOfRooms[25];
    int rooms = 1;
    sf::Text curChar;
private:
};