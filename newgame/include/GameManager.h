#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "GameRoom.h"
#include "GameFloor.h"
#include "Door.h"
#include "Player.h"

using namespace sf;
using namespace fc;
class GameManager :
    public Object
{
public:
    GameManager(Text txt, Core* gameCore);
    GameFloor* currentMap;
    GameRoom* currentRoom;
    Player* player;
    Core* gameCore;
    void Update();
    void Render(RenderWindow* window);
private:
};



