#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"
#include "Door.h"

using namespace sf;
using namespace fc;
enum class RoomState { Solid, Alive, Dead, Start, Boss };
class GameRoom :
	public Object
{
public:
	Vector2f pos;
	Vector2f oppositeDoorPosition(int door);
	GameRoom(int nX, int nY);
	GameRoom();
	bool active = false;
	bool doorsOpen = true;
	void Update();
	void Render(RenderWindow* window);
	void setState(RoomState state);
	Texture* spriteSheet;
	void PlaceDoors(Texture* spriteSheet);
	RoomState getState();
	String stateString();
	GameRoom* neighbors[4];
	Door doors[4];
private:
	RoomState genState;
};