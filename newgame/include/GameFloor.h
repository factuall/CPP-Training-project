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
	sf::RectangleShape mapCell;
	const int floorSize = 20;
	const int genLimit = 20;
	GameFloor() {};
	GameFloor(sf::Text txt);
	void Start();
	void ManagedRender(RenderWindow* window);
	GameRoom roomMap[20][20];
	GameRoom* getNeighbor(int x, int y, int way);
	sf::Vector2f getNeighborV(int x, int y, int way);
	sf::Text curChar;
	bool done = false;
	int playerX = 10;
	int playerY = 10;
	int generations = 1;
private:
};