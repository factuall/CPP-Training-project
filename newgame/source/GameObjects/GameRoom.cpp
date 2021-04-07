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
	for (int ways = 0; ways < 4; ways++)
		doors[ways].active = (neighbors[ways]->getState() != RoomState::Solid && active);
}

void GameRoom::Render(RenderWindow* window) {
	sprite.setPosition(0, 0); // room background
	sprite.setScale(spriteScale());
	window->draw(sprite);

	if (active) {
		for (int ways = 0; ways < 4; ways++) {
			if (neighbors[ways]->getState() != RoomState::Solid) {
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

void GameRoom::Activate(Texture* spriteSheet) {
	for (int ways = 0; ways < 4; ways++) {
		if (neighbors[ways]->getState() != RoomState::Solid) {
			int x = 0, y = 0;
			switch (ways) {
			case 0:
				x = 896;
				y = 240;
				break;
			case 1:
				x = 448;
				y = 0;
				break;
			case 2:
				x = 0;
				y = 240;
				break;
			case 3:
				x = 448;
				y = 448;
				break;
			}
			doors[ways] = Door(x, y, spriteSheet);
			doors[ways].angle = 450 - (ways * 90);
			doors[ways].open = true;
		}
	}

	active = true;
}