#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"
#include "Animation.h"
#include "SpriteController.h"

using namespace sf;
using namespace fc;
class Player :
    public Object
{
public:
    Player(int nX, int nY, Texture* txt);
    void Update();
    void ManagedRender(RenderWindow* window);
    void OnCollision(fc::Collision collision);
    Vector2f velocity;
    Animation bodyAnimation;
    SpriteController animator;
    Sprite headSprite;
private:
    Vector2f input = Vector2f(0, 0);
    int speed = 6;
    const int walkSmoothness = 8;
};