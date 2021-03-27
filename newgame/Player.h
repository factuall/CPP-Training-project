#pragma once
#include "base/Object.h"
#include "base/BoxCollider.h"
class Player :
    public Object
{
public:
    Player(int nX, int nY);
    void Update();
    void OnCollision(Collision collision);
    sf::Vector2f pl;
    sf::Vector2f cl;
    sf::Vector2f kolizjaaa;
    float velocityX = 0, velocityY = 0;
    
private:
    int inputX = 0, inputY = 0, speed = 6;

    const int walkSmoothness = 8;

};