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
    float velocityX = 0, velocityY = 0;
    



private:
    sf::Vector2f input = sf::Vector2f(0, 0);
    int inputX = 0, inputY = 0, speed = 6;

    const int walkSmoothness = 8;
};