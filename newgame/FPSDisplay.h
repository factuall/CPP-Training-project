#pragma once

#include <SFML/Graphics.hpp>

#include "base/Object.h"
class FPSDisplay :
    public Object
{
public:
    FPSDisplay();
    void Render(sf::RenderWindow* window);
};

