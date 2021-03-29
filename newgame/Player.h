#pragma once

#include <SFML/Graphics.hpp>

#include "base/Object.h"
#include "base/BoxCollider.h"
#include "base/Collision.h"

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
    sf::Vector2f normalizedVelocity;
    sf::Vector2f forceBack;
    /////////



private:
    sf::Vector2f input = sf::Vector2f(0, 0);
    int speed = 6;
    const int walkSmoothness = 8;
};