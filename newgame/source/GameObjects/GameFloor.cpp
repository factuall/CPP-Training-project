#include "GameFloor.h"

using namespace sf;
using namespace fc;
GameFloor::GameFloor()
{
}
GameFloor::GameFloor(sf::Text txt) {
	pos.x = 0;
	pos.y = 0;
	id = 0;
	curChar = txt;
	isNull = false;
	collider = new Collider(Vector2f(9999.0f, 9999.0f), Vector2f(0, 0));
	isVisible = true;
	isTrigger = false;
}

void GameFloor::Start()
{
	for (int fX = 0; fX < 26; fX++) {
		if (fX < 20) {
			for (int fY = 0; fY < 20; fY++) {
				roomMap[fX][fY] = GameRoom();
			}
		}
	}
	roomMap[10][10] = GameRoom(10, 10);
	rooms = 0;
}

void GameFloor::ManagedRender(RenderWindow* window) {
	if (rooms < 25) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 8);
		for (int fX = 0; fX < 20; fX++) {
			for (int fY = 0; fY < 20; fY++) {
				if (roomMap[fX][fY].getState() == RoomState::Alive) {
					int nbrX = 0; int nbrY = 0;
					for (int ways = 0; ways < 4; ways++) {
						switch (ways) {
						case 0:
							if (fX == 19) continue;
							nbrX = fX + 1;
							nbrY = fY;
							break;
						case 1:
							if (fY == 0) continue;
							nbrX = fX;
							nbrY = fY - 1;
							break;
						case 2:
							if (fX == 0) continue;
							nbrX = fX - 1;
							nbrY = fY;
							break;
						case 3:
							if (fY == 19) continue;
							nbrX = fX;
							nbrY = fY + 1;
							break;
						}

						if (roomMap[nbrX][nbrY].getState() == RoomState::Dead) continue;
						else if (roomMap[nbrX][nbrY].getState() == RoomState::Solid) {
							if (dist(rng) > 3) {
								roomMap[nbrX][nbrY].setState(RoomState::Alive);
								rooms++;
							}
							else {
								roomMap[nbrX][nbrY].setState(RoomState::Dead);
							}
							roomMap[nbrX][nbrY].pos.x = nbrX;
							roomMap[nbrX][nbrY].pos.y = nbrY;
						}
					}
				}
			}
		}
	}
	else {
		for (int fX = 0; fX < 20; fX++) {
			for (int fY = 0; fY < 20; fY++) {
				if (roomMap[fX][fY].getState() == RoomState::Solid) {
					roomMap[fX][fY].pos.x = fX;
					roomMap[fX][fY].pos.y = fY;
				}
			}
		}
		for (int fX = 0; fX < 20; fX++) {
			for (int fY = 0; fY < 20; fY++) {
				if (roomMap[fX][fY].getState() != RoomState::Solid) {
					curChar.setCharacterSize(20);
					curChar.setFillColor(Color(100, 100, 100, 255));
					curChar.setPosition(fX * 20 + 25, fY * 20 + 26);
					if (fX == playerX && fY == playerY) curChar.setFillColor(Color(100, 255, 100, 255));
					window->draw(curChar);
				}
				else {
					curChar.setCharacterSize(20);
					curChar.setFillColor(Color(100, 100, 100, 50));
					curChar.setPosition(fX * 20 + 25, fY * 20 + 26);
					window->draw(curChar);
				}
			}
		}
	}
}

GameRoom* GameFloor::getNeighbor(int x, int y, int way) {
	int nbrX = 0; int nbrY = 0;
	switch (way) {
	case 0:
		nbrX = x + 1;
		nbrY = y;
		break;
	case 1:
		nbrX = x;
		nbrY = y - 1;
		break;
	case 2:
		nbrX = x - 1;
		nbrY = y;
		break;
	case 3:
		nbrX = x;
		nbrY = y + 1;
		break;
	}
	return &roomMap[nbrX][nbrY];
}

sf::Vector2f GameFloor::getNeighborV(int x, int y, int way)
{
	int nbrX = 0; int nbrY = 0;
	switch (way) {
	case 0:
		nbrX = x + 1;
		nbrY = y;
		break;
	case 1:
		nbrX = x;
		nbrY = y - 1;
		break;
	case 2:
		nbrX = x - 1;
		nbrY = y;
		break;
	case 3:
		nbrX = x;
		nbrY = y + 1;
		break;
	}
	return sf::Vector2f(nbrX, nbrY);
}