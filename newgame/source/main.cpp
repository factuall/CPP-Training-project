#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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
#include "GameManager.h"
#include "Core.h"
#include "Door.h"
#include "DebugCore.h"

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

	Object ghostObject = Object(100, -100);
	ghostObject.collider = new Collider(sf::Vector2f(-100, -100), sf::Vector2f(0, 0));
	ghostObject.isVisible = false;
	gameCore.addObject(&ghostObject);



	sf::Text gfTXT;
	gfTXT.setFont(fontAlternative);
	gfTXT.setString("X");
	GameManager gm = GameManager(gfTXT, &gameCore);
	gameCore.addObject(&gm);

	sf::Text txt;
	txt.setFont(fontRegular);
	txt.setString("00");
	FPSDisplay fpsDisplay = FPSDisplay(txt);
	gameCore.addObject(&fpsDisplay);

	{ //walls and background
		fc::Object* Walls[100] = {};
		for (int w = 0; w < 14; w++) {
			Walls[w] = new fc::Object(64 * w + 64, 16);
			Walls[w]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w]->collider = new Collider(sf::Vector2f(Walls[w]->pos.x, Walls[w]->pos.y), sf::Vector2f(64, 64));
			Walls[w]->isVisible = false;
			gameCore.addObject(Walls[w]);

			Walls[w + 14] = new fc::Object(64 * w + 64, 512 - 32);
			Walls[w + 14]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 14]->collider = new Collider(sf::Vector2f(Walls[w + 14]->pos.x, Walls[w + 14]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 14]->isVisible = false;
			gameCore.addObject(Walls[w + 14]);

			Walls[w + 28] = new fc::Object(16, 64 * w + 32);
			Walls[w + 28]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 28]->collider = new Collider(sf::Vector2f(Walls[w + 28]->pos.x, Walls[w + 28]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 28]->isVisible = false;
			gameCore.addObject(Walls[w + 28]);

			Walls[w + 42] = new fc::Object(1024-64-16, 64 * w + 32);
			Walls[w + 42]->sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 32, 32, 32));
			Walls[w + 42]->collider = new Collider(sf::Vector2f(Walls[w + 42]->pos.x, Walls[w + 42]->pos.y), sf::Vector2f(64, 64));
			Walls[w + 42]->isVisible = false;
			gameCore.addObject(Walls[w + 42]);
		}
		Walls[6]->Move(Vector2f(-20, -16));
		Walls[6]->collider = new Collider(Walls[6]->pos, Vector2f(64, 64), ColliderType::CircleType);
		Walls[7]->Move(Vector2f(20, -16));
		Walls[7]->collider = new Collider(Walls[7]->pos, Vector2f(64, 64), ColliderType::CircleType);

		Walls[14 + 6]->Move(Vector2f(-25, 0));
		Walls[14 + 6]->collider = new Collider(Walls[14 + 6]->pos, Vector2f(64, 64), ColliderType::CircleType);
		Walls[14 + 7]->Move(Vector2f(25, 0));
		Walls[14 + 7]->collider = new Collider(Walls[14 + 7]->pos, Vector2f(64, 64), ColliderType::CircleType);

		Walls[28 + 3]->Move(Vector2f(0, -25));
		Walls[28 + 3]->collider = new Collider(Walls[28 + 6]->pos, Vector2f(64, 64), ColliderType::CircleType);
		Walls[28 + 4]->Move(Vector2f(0, 25));
		Walls[28 + 4]->collider = new Collider(Walls[28 + 7]->pos, Vector2f(64, 64), ColliderType::CircleType);

		Walls[42 + 3]->Move(Vector2f(0, -25));
		Walls[42 + 3]->collider = new Collider(Walls[42 + 6]->pos, Vector2f(64, 64), ColliderType::CircleType);
		Walls[42 + 4]->Move(Vector2f(0, 25));
		Walls[42 + 4]->collider = new Collider(Walls[42 + 7]->pos, Vector2f(64, 64), ColliderType::CircleType);
	} //walls
	

	//playerObj.sprite = sf::Sprite(gameCore.spriteSheet, sf::IntRect(0, 0, 32, 32));
	//playerObj.sprite.setColor(sf::Color(150, 255, 150, 255));



	///
	DebugCore* debugger = new DebugCore(&gameCore, &image, &fontRegular);
	while (gameCore.window->isOpen()) {
		sf::Event event;
		while (gameCore.window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gameCore.window->close();
				debugger->debugWindow->close();
			}

		}
		sf::Event debuggerEvent;
		while (debugger->debugWindow->pollEvent(debuggerEvent)) {
			if (debuggerEvent.type == sf::Event::Closed) {
				gameCore.window->close();
				debugger->debugWindow->close();
			}
			debugger->debugGui->handleEvent(debuggerEvent);
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
			debugger->Update();
		}
		fpsDisplay.text.setString(std::to_string(framesPerSecond));
		gameCore.render();
		debugger->Render();
	}
	return 0;
}