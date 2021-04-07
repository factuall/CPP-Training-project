#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"

namespace fc {
	using namespace sf;

	const int objLimit = 1000;
	class Core
	{
	public:
		Core(Image* img, Font* fnt, Font* altFnt);
		void run();
		void addObject(Object* newObject);
		void deleteObject(int id);
		Object* getObject(int id);
		RenderWindow* window;
		Image image;
		Texture spriteSheet;
		Font fontRegular;
		Font fontAlternative;
		void update();
		void render();
	private:
		Object* Objects[objLimit];
	};
}
