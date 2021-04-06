#pragma once
#include "SFML/Graphics.hpp"
#include "Core.h"
#include "Animation.h"

namespace fc {
	using namespace sf;

	class SpriteController {
	public:
		SpriteController() {};
		SpriteController(Texture* spriteSource, Animation* startAnimation);
		Sprite output;
		Texture* spriteSource;
		Vector2i baseOffset; 
		Animation* currentAnimation;
		void Update();
	};

}