#pragma once
#include "SFML/Graphics.hpp"
#include "Core.h"
namespace fc {
	using namespace sf;
	class Animation {
	public:
		bool loop;
		int animationDelay;
		Animation(Vector2i offset, Vector2i frameSize, int animationLength, int delay);
		void setFrame(int frame);
		void Toggle();
		void Play();
		void Pause();
		void Resume();
		void Stop();
		void Update();
		IntRect getCurrentSprite();
		void setCurrentFrame(int frame);
	private:
		IntRect currentSprite;
		Vector2i frameSize;
		Vector2i offset;
		bool playing;
		int waitTime;
		int currentFrame;
		int length;
	};
}
