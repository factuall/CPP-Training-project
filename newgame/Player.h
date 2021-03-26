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

private:
    int inputX = 0, inputY = 0, speed = 6;
    float velocityX = 0, velocityY = 0;
    const int walkSmoothness = 8;
};