#include "Animation.h"
#include "SFML/Graphics.hpp"

namespace fc {
	using namespace sf;

	Animation::Animation(Vector2i offset, Vector2i frameSize, int animationLength, int delay)
	{
		this->offset = offset;
		this->frameSize = frameSize;
		this->animationDelay = delay;
		this->length = animationLength;
		currentFrame = 0;
		currentSprite = IntRect(offset.x, offset.y, frameSize.x, frameSize.y);
	}
	IntRect Animation::getCurrentSprite() {
		return currentSprite;
	}
	void Animation::Update() {
		if (playing) {
			if(waitTime >= animationDelay){
				setCurrentFrame(currentFrame + 1);
				waitTime = 0;
			}
			else waitTime++; 
		}
		currentSprite.left = offset.x + (frameSize.x * currentFrame);
		currentSprite.top = offset.y + (frameSize.y * currentFrame);
	}
	void Animation::setCurrentFrame(int frame) {
		if (this->length > frame) currentFrame = frame;
		else currentFrame = 0;
	}
	void Animation::Play() {
		setCurrentFrame(0);
		playing = true;
	}
	void Animation::Resume() {
		playing = true;
	}
	void Animation::Stop() {
		setCurrentFrame(0);
		playing = false;
	}
	void Animation::Pause() {
		playing = false;
	}
}