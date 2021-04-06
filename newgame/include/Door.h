#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Animation.h"
#include "SpriteController.h"

using namespace sf;
using namespace fc;
class Door:
    public Object
{
public:
    Door();
    Door(int nX, int nY, Texture* txt);
    void Update();
    void Render(RenderWindow* window);
    SpriteController animator;
    Animation doorAnimation;
private:
};