#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"
#include "GameRoom.h"

using namespace sf;
using namespace fc;
class GameFloor :
	public Object
{
public:
	GameFloor();
	GameFloor(sf::Text txt);
	void Start();
	void ManagedRender(RenderWindow* window);
	char room[20][20];
	GameRoom roomMap[20][20];
	GameRoom* getNeighbor(int x, int y, int way);
	sf::Vector2f getNeighborV(int x, int y, int way);
	int rooms = 1;
	sf::Text curChar;
	bool isDone = false;
	int playerX = 10;
	int playerY = 10;
private:
};