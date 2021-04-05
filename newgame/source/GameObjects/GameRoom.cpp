#include "GameRoom.h"

using namespace sf;
using namespace fc;
GameRoom::GameRoom(int nX, int nY, int gen) {
	pos.x = nX;
	pos.y = nY;
	id = 0;
	isNull = false;
	collider = new Collider(Vector2f(0, 0), Vector2f(0, 0));
	isVisible = true;
	isTrigger = false;
	genState = RoomState::Alive;
	generation = gen;
};

GameRoom::GameRoom() {
	pos.x = 0;
	pos.y = 0;
	id = 0;
	isNull = true;
	collider = nullptr;
	isVisible = false;
	isTrigger = false;
	genState = RoomState::Solid;
};

void GameRoom::Update() {

}

void GameRoom::Render(RenderWindow* window) {
	sprite.setPosition(pos);
	sprite.setScale(spriteScale());
	window->draw(sprite);
}

void GameRoom::OnCollision(fc::Collision collision) {
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
