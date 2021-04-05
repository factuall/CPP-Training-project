#include "SpriteController.h"
#include "SFML/Graphics.hpp"
#include "Core.h"

namespace fc {
	using namespace sf;

	SpriteController::SpriteController(Texture* spriteSource, Animation startAnimation) {
		this->spriteSource = spriteSource;
		output = Sprite(*spriteSource, startAnimation.getCurrentSprite());
	}

	void SpriteController::Update() {
		currentAnimation.Update();
	}


}
