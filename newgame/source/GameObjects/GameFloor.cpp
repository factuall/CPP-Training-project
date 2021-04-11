#include "GameFloor.h"

using namespace sf;
using namespace fc;
GameFloor::GameFloor() {
	mapCell = RectangleShape(Vector2f(5,5));
	pos.x = 0;
	pos.y = 0;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(9999.0f, 9999.0f), Vector2f(0, 0));
	isVisible = true;
	isTrigger = false;
}

void GameFloor::Start()
{
	for (int roomX = 0; roomX < genLimit + 1; roomX++) {
		if (roomX < floorSize) {
			for (int roomY = 0; roomY < floorSize; roomY++) {
				roomMap[roomX][roomY] = GameRoom();
			}
		}
	}
	roomMap[floorSize/2][floorSize/2] = GameRoom(floorSize/2, floorSize/2);
	generations = 0;
}

bool once = false;
void GameFloor::ManagedRender(RenderWindow* window) {
	if (generations < genLimit) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 8);
		for (int roomX = 0; roomX < floorSize; roomX++) {
			for (int roomY = 0; roomY < floorSize; roomY++) {
				if (roomMap[roomX][roomY].getState() == RoomState::Alive) {
					int neighborX = 0; int neighborY = 0;
					for (int ways = 0; ways < 4; ways++) {
						switch (ways) {
						case 0:
							if (roomX == 19) continue;
							neighborX = roomX + 1;
							neighborY = roomY;
							break;
						case 1:
							if (roomY == 0) continue;
							neighborX = roomX;
							neighborY = roomY - 1;
							break;
						case 2:
							if (roomX == 0) continue;
							neighborX = roomX - 1;
							neighborY = roomY;
							break;
						case 3:
							if (roomY == 19) continue;
							neighborX = roomX;
							neighborY = roomY + 1;
							break;
						}

						if (roomMap[neighborX][neighborY].getState() == RoomState::Dead) continue;
						else if (roomMap[neighborX][neighborY].getState() == RoomState::Solid) {
							if (dist(rng) > 3) {
								roomMap[neighborX][neighborY].setState(RoomState::Alive);
								generations++;
							}
							else {
								roomMap[neighborX][neighborY].setState(RoomState::Dead);
							}
							roomMap[neighborX][neighborY].pos.x = neighborX;
							roomMap[neighborX][neighborY].pos.y = neighborY;
						}
					}
				}
			}
		}
	}
	else {
		if (!once) {
			for (int roomX = 0; roomX < floorSize; roomX++) {
				for (int roomY = 0; roomY < floorSize; roomY++) {
					if (roomMap[roomX][roomY].getState() == RoomState::Solid) {
						roomMap[roomX][roomY].pos.x = roomX;
						roomMap[roomX][roomY].pos.y = roomY;
					}
				}
			}
			once = true;
		}
		for (int roomX = 0; roomX < floorSize; roomX++) {
			for (int roomY = 0; roomY < floorSize; roomY++) {
				if (roomMap[roomX][roomY].getState() == RoomState::Alive) {
					mapCell.setFillColor(Color(100, 100, 100, 255));
					mapCell.setPosition(roomX * 6 + 25, roomY * 6 + 26);
					if (roomX == playerX && roomY == playerY) mapCell.setFillColor(Color(100, 255, 100, 255));
					window->draw(mapCell);
				}
				else {
					mapCell.setFillColor(Color(100, 100, 100, 50));
					mapCell.setPosition(roomX * 6 + 25, roomY * 6 + 26);
					window->draw(mapCell);
				}
			}
		}
	}
}

GameRoom* GameFloor::getNeighbor(int x, int y, int way) {
	int neighborX = 0; int neighborY = 0;
	switch (way) {
	case 0:
		neighborX = x + 1;
		neighborY = y;
		break;
	case 1:
		neighborX = x;
		neighborY = y - 1;
		break;
	case 2:
		neighborX = x - 1;
		neighborY = y;
		break;
	case 3:
		neighborX = x;
		neighborY = y + 1;
		break;
	}
	return &roomMap[neighborX][neighborY];
}

sf::Vector2f GameFloor::getNeighborV(int x, int y, int way)
{
	int neighborX = 0; int neighborY = 0;
	switch (way) {
	case 0:
		neighborX = x + 1;
		neighborY = y;
		break;
	case 1:
		neighborX = x;
		neighborY = y - 1;
		break;
	case 2:
		neighborX = x - 1;
		neighborY = y;
		break;
	case 3:
		neighborX = x;
		neighborY = y + 1;
		break;
	}
	return sf::Vector2f(neighborX, neighborY);
}