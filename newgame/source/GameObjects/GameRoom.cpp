#include "GameRoom.h"
#include <iostream>


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

	void Init();
};

GameRoom::GameRoom() {
	genState = RoomState::Solid;
	pos.x = 0;
	pos.y = 0;
	id = 0;
	isNull = true;
	collider = nullptr;
	isVisible = false;
	isTrigger = false;

};

void GameRoom::Update() {

}

void GameRoom::Render(RenderWindow* window) {

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

void GameRoom::Enter() {

}