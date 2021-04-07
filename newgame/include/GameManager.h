#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "GameRoom.h"
#include "GameFloor.h"
#include "Door.h"
#include "Player.h"

using namespace sf;
using namespace fc;
class GameManager :
	public Object
{
public:
	GameManager(Text txt, Core* gameCore);
	sf::View windowView = sf::View(Vector2f(512.f, 288.f), Vector2f(1024.f, 576.f));
	GameFloor* currentMap;
	GameRoom* currentRoom;
	GameRoom* transitionRoom;
	Player* player;
	Core* gameCore;
	void Update();
	void Render(RenderWindow* window);
	void InitalizeRoom(int x, int y);
	void InitTransitionRoom(int x, int y, Vector2f nextRoom);
	bool transitionPlaying = false;
private:
};
