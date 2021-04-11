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
	View gameView;

	GameManager(Text txt, Core* gameCore);
	void Update();
	void Render(RenderWindow* window);
	Core* gameCore;

	//map management
	GameFloor* currentMap;
	GameRoom* currentRoom;
	void InitalizeRoom(int x, int y);
	//map transitions
	GameRoom* destRoom;
	int doorToDestRoom;
	int transitionTime = 0;
	bool transitionGoing = false;

	Player* player;
private:
	bool initalized;
};
