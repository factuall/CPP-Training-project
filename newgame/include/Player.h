#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"

using namespace sf;
using namespace fc;
class Player :
    public Object
{
public:
    Player(int nX, int nY);
    void Update();
    void Render(RenderWindow* window);
    void OnCollision(fc::Collision collision);
    Vector2f velocity;

    ////////
    ////////
    Vector2f lastColliderPosition;
    Vector2f destVector;
    Vector2f normalizedVelocity;
    Vector2f forceBack;
    /////////



private:
    Vector2f input = Vector2f(0, 0);
    int speed = 6;
    const int walkSmoothness = 8;
};