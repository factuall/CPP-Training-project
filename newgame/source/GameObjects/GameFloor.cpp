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
	for (int fX = 0; fX < 25; fX++) {
		if (fX < 20) {
			for (int fY = 0; fY < 20; fY++) {
				roomMap[fX][fY] = GameRoom();

			}
		}
		orderOfRooms[fX] = Vector2i(0, 0);

	}
	orderOfRooms[0] = Vector2i(10, 10);
	roomMap[10][10] = GameRoom(10, 10, 0);
	rooms = 0;
}

void GameFloor::Render(RenderWindow* window) {
	if (rooms < 25) {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, 8);
		for (int fX = 0; fX < 20; fX++) {
			for (int fY = 0; fY < 20; fY++) {
				if (roomMap[fX][fY].getState() == RoomState::Alive) {
					for (int ways = 0; ways < 4; ways++) {
						int nbrX = 0; int nbrY = 0;
						switch (ways) {
						case 0:
							nbrX = fX + 1;
							nbrY = fY;
							break;
						case 1:
							nbrX = fX;
							nbrY = fY + 1;
							break;
						case 2:
							nbrX = fX - 1;
							nbrY = fY;
							break;
						case 3:
							nbrX = fX;
							nbrY = fY - 1;
							break;
						}


						if (roomMap[nbrX][nbrY].getState() == RoomState::Dead) {
							continue;
						}
						else if (roomMap[nbrX][nbrY].getState() == RoomState::Solid) {
							if (dist(rng) > 3) {
								roomMap[nbrX][nbrY].setState(RoomState::Alive);
								orderOfRooms[rooms] = Vector2i(nbrX, nbrY);
								rooms++;
								return;
							}
							else {
								roomMap[fX][fY].setState(RoomState::Dead);
							}
						}
					}
				}
			}
		}
		
	}
	else {
		orderOfRooms[0] = Vector2i(10, 10);
		for (int order = 0; order < 25; order++) {
			if ((orderOfRooms[order].x + orderOfRooms[order].y) != 0) {
				curChar.setCharacterSize(20);
				if (order == 4) {
					curChar.setFillColor(sf::Color(0,255,0,255));
				}
				else if(order == 24){
					curChar.setFillColor(sf::Color(255,0,0,255));
				}
				else {
					curChar.setFillColor(sf::Color(order * 8, order * 8, 255, 255));
				}
				curChar.setPosition(orderOfRooms[order].x * 20 + 25, (orderOfRooms[order].y * 20 + 26));

				window->draw(curChar);
			}
		}
	}
}
