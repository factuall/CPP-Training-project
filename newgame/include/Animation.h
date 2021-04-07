#pragma once
#include "SFML/Graphics.hpp"
#include "Core.h"
namespace fc {
	using namespace sf;
	class Animation {
	public:
		bool loop;
		bool playReverse = false;
		int animationDelay;
		Animation();
		Animation(Vector2i offset, Vector2i frameSize, int animationLength, int delay);
		void Toggle();
		void Play();
		void Pause();
		void Resume();
		void Stop();
		void Update();
		IntRect getCurrentSprite();
		void setCurrentFrame(int frame);
		int getCurrentFrame();
		int getLength();
		bool isPlaying();
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
