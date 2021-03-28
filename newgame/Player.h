#pragma once

#include <SFML/Graphics.hpp>

#include "base/Object.h"
#include "base/BoxCollider.h"
class Player :
    public Object
{
public:
    Player(int nX, int nY);
    void Update();
    void Render(sf::RenderWindow* window);
    void OnCollision(Collision collision);
    sf::Vector2f velocity;
    
    ////////
    sf::Vector2f lastColliderPosition;
    sf::Vector2f destVector;
    /////////



private:
    sf::Vector2f input = sf::Vector2f(0, 0);
    int speed = 6;

    const int walkSmoothness = 8;
};