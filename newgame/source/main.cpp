#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <chrono>
#include <time.h>

#include "Collision.h"
#include "Collider.h"
#include "Object.h"
#include "FPSDisplay.h"
#include "Player.h"
#include "Core.h"




int lastTick, deltaTime;
int lastTime = 0; double deltaTIme;
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 100000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
int RelativeTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq / 100.0;
}
int SystemTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart) / PCFreq / 100.0;
}
int DeltaTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	double now = (double(li.QuadPart) / PCFreq) / 100.0;
	if (lastTime == 0) lastTime = (int)now;
	deltaTime = (int)now - lastTime;
	lastTime = (int)now;
	return deltaTime;
}

int skipTickTime = 0;
int main()
{
	sf::Image image;
	sf::Font fontRegular;
	sf::Font fontAlternative;
	if (!image.loadFromFile("../Release/img/sheet.png") ||
		!fontRegular.loadFromFile("../Release/fonts/suture.ttf") ||
		!fontAlternative.loadFromFile("../Release/fonts/future.ttf")) {
		//ERROR
	}
	StartTimer();
	fc::Core gameCore = fc::Core(&image, &fontRegular, &fontAlternative);
	fc::Object Wall = fc::Object(128, 128);
	Wall.sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(32, 0, 32, 32));
	Wall.collider = new Collider(sf::Vector2f(Wall.pos.x, Wall.pos.y),sf::Vector2f(64, 64), fc::ColliderType::CircleType);
	Wall.isVisible = true;
	gameCore.addObject(&Wall);

	Player playerObj = Player(300, 300);
	playerObj.sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 0, 32, 32));
	playerObj.sprite.setColor(sf::Color(150, 255, 150, 255));
	gameCore.addObject(&playerObj);

	while (gameCore.window->isOpen()) {
		sf::Event event;
		while (gameCore.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameCore.window->close();
		}

		if (DeltaTime() <= 16 && skipTickTime < 16) {
			skipTickTime += deltaTime;
		}
		if (skipTickTime >= 16) {
			skipTickTime = 0;
			gameCore.update();
		}
		gameCore.render();
	}

	/*
	fpsDisplay = FPSDisplay();
	fpsDisplay.text.setFont(fontRegular);
	fpsDisplay.text.setString(std::to_string(framesPerSecond));
	addObject(&fpsDisplay);
	*/
	return 0;
}