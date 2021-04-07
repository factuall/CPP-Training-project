#include "Animation.h"
#include "SFML/Graphics.hpp"

namespace fc {
	using namespace sf;
	Animation::Animation() {
	}
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
			if (waitTime >= animationDelay) {
				setCurrentFrame((playReverse) ? currentFrame - 1 : currentFrame + 1);
				waitTime = 0;
			}
			else waitTime++;
		}
		currentSprite.left = offset.x + (frameSize.x * currentFrame);
		currentSprite.top = offset.y;
	}
	void Animation::setCurrentFrame(int frame) {
		if (loop) {
			if (frame < 0) currentFrame = length - 1;
			else if (frame >= length) currentFrame = 0;
			else currentFrame = frame;
		}
		else if (frame < 0 || frame >= length) playing = false;
		else currentFrame = frame;
	}
	void Animation::Play() {
		setCurrentFrame((playReverse) ? length - 1 : 0);
		playing = true;
	}
	void Animation::Resume() {
		playing = true;
	}
	void Animation::Stop() {
		setCurrentFrame((playReverse) ? length - 1 : 0);
		playing = false;
	}
	void Animation::Pause() {
		playing = false;
	}
	int Animation::getCurrentFrame() {
		return currentFrame;
	}
	int Animation::getLength()
	{
		return length;
	}
	bool Animation::isPlaying()
	{
		return playing;
	}
}