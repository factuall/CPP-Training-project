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
#include "GameFloor.h"
#include "Core.h"

int lastTick, deltaTime, secondCounter = 0, framesPerSecond = 0, framesInSecond = 0;
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

	///
	
	StartTimer();
	fc::Core gameCore = fc::Core(&image, &fontRegular, &fontAlternative);

	{ //walls
		fc::Object* Walls[100] = {};
		for (int w = 0; w < 14; w++) {
			Walls[w] = new fc::Object(64 * w + 420, 64);
			Walls[w]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w]->collider = new Collider(sf::Vector2f(Walls[w]->pos.x, Walls[w]->pos.y), sf::Vector2f(64, 64));
			Walls[w]->isVisible = true;
			gameCore.addObject(Walls[w]);

			Walls[w + 14] = new fc::Object(64 * w + 420, 448);
			Walls[w + 14]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 14]->collider = new Collider(sf::Vector2f(Walls[w + 14]->pos.x, Walls[w + 14]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 14]->isVisible = true;
			gameCore.addObject(Walls[w + 14]);

			Walls[w + 28] = new fc::Object(420, 64 * w + 64);
			Walls[w + 28]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 28]->collider = new Collider(sf::Vector2f(Walls[w + 28]->pos.x, Walls[w + 28]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 28]->isVisible = true;
			gameCore.addObject(Walls[w + 28]);

			Walls[w + 42] = new fc::Object(920, 64 * w + 64);
			Walls[w + 42]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 42]->collider = new Collider(sf::Vector2f(Walls[w + 42]->pos.x, Walls[w + 42]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 42]->isVisible = true;
			gameCore.addObject(Walls[w + 42]);


		}
		Walls[56] = new fc::Object(560, 256);
		Walls[56]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(32, 0, 32, 32));
		Walls[56]->collider = new Collider(sf::Vector2f(Walls[56]->pos.x, Walls[56]->pos.y), sf::Vector2f(64, 64), fc::ColliderType::CircleType);
		Walls[56]->isVisible = true;
		gameCore.addObject(Walls[56]);
	} //walls

	sf::Text gfTXT;
	gfTXT.setFont(fontAlternative);
	gfTXT.setString("X");
	GameFloor gf = GameFloor(gfTXT);
	gameCore.addObject(&gf);

	Player playerObj = Player(560, 340);
	playerObj.sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 0, 32, 32));
	playerObj.sprite.setColor(sf::Color(150, 255, 150, 255));
	gameCore.addObject(&playerObj);

	sf::Text txt;
	txt.setFont(fontRegular);
	txt.setString("00");
	FPSDisplay fpsDisplay = FPSDisplay(txt);
	gameCore.addObject(&fpsDisplay);

	///

	while (gameCore.window->isOpen()) {
		sf::Event event;
		while (gameCore.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameCore.window->close();
		}

		if (DeltaTime() <= 16 && skipTickTime < 16) {
			skipTickTime += deltaTime;
		}
		secondCounter += deltaTime;
		if (secondCounter >= 1000) {
			framesPerSecond = framesInSecond;
			framesInSecond = 0;
			secondCounter = 0;
		}
		if (skipTickTime >= 16) {
			skipTickTime = 0;
			framesInSecond++;
			gameCore.update();
		}
		fpsDisplay.text.setString(std::to_string(framesPerSecond));
		gameCore.render();
	}
	return 0;
}