#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"

using namespace sf;
using namespace fc;
class ObjectExample :
	public Object
{
public:
	ObjectExample(int nX, int nY);
	void Update();
	void Render(RenderWindow* window);
	void OnCollision(fc::Collision collision);
private:
};