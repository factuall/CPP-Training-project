#pragma once
#include "base/Object.h"
class Player :
    public Object
{
public:
    Player(int nX, int nY);
    void Update();
    void OnCollision(Object *collider);

private:
    int inputX = 0, inputY = 0, speed = 6;
    float velocityX = 0, velocityY = 0;
    const int walkSmoothness = 8;
};