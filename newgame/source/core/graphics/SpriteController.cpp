#include "SpriteController.h"
#include "SFML/Graphics.hpp"
#include "Core.h"

namespace fc {
	using namespace sf;

	SpriteController::SpriteController(Texture* spriteSheet, Animation* startAnimation) {
		this->spriteSource = spriteSheet;
		currentAnimation = startAnimation;
		output = Sprite(*spriteSheet, currentAnimation->getCurrentSprite());
	}

	void SpriteController::Update() {
		currentAnimation->Update();
		output = Sprite(*spriteSource, currentAnimation->getCurrentSprite());
	}
}