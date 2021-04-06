#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"
#include "GameRoom.h"

using namespace sf;
using namespace fc;
class GameFloor :
    public Object
{
public:
    GameFloor();
    GameFloor(sf::Text txt);
    void Start();
    void Render(RenderWindow* window);
    char room[20][20];
    GameRoom roomMap[20][20];
    Vector2i orderOfRooms[25];
    int rooms = 1;
    sf::Text curChar;
    bool isDone = false;
private:
};