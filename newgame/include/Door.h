#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Animation.h"
#include "SpriteController.h"

using namespace sf;
using namespace fc;
class Door :
	public Object
{
public:
	Door();
	Door(int nX, int nY, int offX, int offY, Texture* txt);
	void Update();
	void ManagedRender(RenderWindow* window);
	void Render(RenderWindow* window) {};
	void OnCollision(Collision collision);
	SpriteController animator;
	Animation* doorAnimation;
	bool active = false;
	bool open = true;
	bool entered = false;
	int angle = 0, offX = 0, offY = 0;
private:
};