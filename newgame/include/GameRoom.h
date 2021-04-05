#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"
#include "Object.h"

using namespace sf;
using namespace fc;
enum class RoomState{Solid, Alive, Dead, Start, Boss};
class GameRoom :
    public Object
{
public:
    GameRoom(int nX, int nY, int gen);
    GameRoom();
    void Update();
    void Render(RenderWindow* window);
    void OnCollision(fc::Collision collision);
    RoomState genState;
    void setState(RoomState state);
    RoomState getState();
    String stateString();
    int generation;
private:
};