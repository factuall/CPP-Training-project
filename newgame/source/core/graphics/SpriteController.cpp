#include "SpriteController.h"
#include "SFML/Graphics.hpp"
#include "Core.h"

namespace fc {
	using namespace sf;

	SpriteController::SpriteController(Texture* spriteSource, Animation* startAnimation) {
		this->spriteSource = spriteSource;
		currentAnimation = startAnimation;
		output = Sprite(*spriteSource, currentAnimation->getCurrentSprite());
	}

	void SpriteController::Update() {
		currentAnimation->Update();
		output = Sprite(*spriteSource, currentAnimation->getCurrentSprite());
	}
}