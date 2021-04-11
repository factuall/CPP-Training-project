#include "GameRoom.h"
#include <iostream>

using namespace sf;
using namespace fc;
GameRoom::GameRoom(int nX, int nY) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(0, 0), Vector2f(0, 0));
	isVisible = true;
	isTrigger = false;
	genState = RoomState::Alive;
};

GameRoom::GameRoom() {
	pos.x = 0;
	pos.y = 0;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(0, 0), Vector2f(0, 0));
	isVisible = true;
	isTrigger = false;
	genState = RoomState::Solid;
};

void GameRoom::Update() {
	for (int ways = 0; ways < 4; ways++) {
		doors[ways].active = (neighbors[ways]->getState() == RoomState::Alive && active);
		doors[ways].open = doorsOpen;
	}
	if (Keyboard::isKeyPressed(Keyboard::O)) {
		doorsOpen = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::P)) {
		doorsOpen = true;
	}
}

void GameRoom::Render(RenderWindow* window) {
	sprite.setScale(spriteScale());
	window->draw(sprite);

	if (active) {
		for (int ways = 0; ways < 4; ways++) {
			if (neighbors[ways]->getState() == RoomState::Alive) {
				doors[ways].ManagedRender(window);
			}
		}
	}
}

void GameRoom::setState(RoomState state)
{
	this->genState = state;
}

RoomState GameRoom::getState()
{
	return genState;
}

String GameRoom::stateString()
{
	switch (genState) {
	case RoomState::Alive:
		return "A";
		break;
	case RoomState::Solid:
		return "#";
		break;
	case RoomState::Dead:
		return "D";
		break;
	case RoomState::Start:
		return "S";
		break;
	case RoomState::Boss:
		return "X";
		break;
	default:
		return "#";
	}
}

void GameRoom::PlaceDoors(Texture* spriteSheet) {
	for (int ways = 0; ways < 4; ways++) {
		if (neighbors[ways]->getState() == RoomState::Alive) {
			int x = 0, y = 0, offX = 0, offY = 0;
			switch (ways) {
			case 0:
				x = 896;
				y = 224;
				offX = 28;
				break;
			case 1:
				x = 448;
				y = 0;
				offY = -48;
				break;
			case 2:
				x = 0;
				y = 224;
				offX = -28;
				break;
			case 3:
				x = 448;
				y = 448;
				offY = 16;
				break;
			}
			doors[ways] = Door(x, y, offX, offY, spriteSheet);
			doors[ways].angle = 450 - (ways * 90);
			doors[ways].open = true;
		}
	}
	active = true;
}

Vector2f GameRoom::oppositeDoorPosition(int door) {
	Vector2f result;
	switch (door) {
	case 0:
		result.x = 80;
		break;
	case 1:
		result.y = 420;
		break;
	case 2:
		result.x = 880;
		break;
	case 3:
		result.y = 68;
		break;
	}
	return result;
}