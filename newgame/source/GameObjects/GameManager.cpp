#include "GameManager.h"
#include <iostream>

using namespace sf;
using namespace fc;
GameManager::GameManager(Text txt, Core* gameCore) {
	//rendering

	gameView = View(Vector2f(512, 288), Vector2f(1024, 576));
	//object
	id = 0;
	isNull = false;
	isVisible = true;
	isTrigger = false;
	this->gameCore = gameCore;
	collider = new Collider(Vector2f(-21, -37), Vector2f(0, 0));
	initalized = false;
};

int generationTime = 0;
void GameManager::Update() {
	if (!initalized) {
		//map
		currentMap = new GameFloor();
		gameCore->addObject(currentMap);
		currentMap->Start();
		//player
		player = new Player(560, 340, &gameCore->spriteSheet);
		gameCore->addObject(player);

		initalized = true;
		return;
	}
	if (!currentMap->done && currentMap->generations < currentMap->genLimit) {
		generationTime++;
		if (generationTime > 10) {
			currentMap->Start();
			generationTime = 0;
		}
	}
	else if (currentMap->generations >= currentMap->genLimit && !currentMap->done) {
		currentMap->done = true;
		InitalizeRoom(currentMap->floorSize/2, currentMap->floorSize / 2);
		for (int startClose = 0; startClose < 4; startClose++) {
			if (currentRoom->neighbors[startClose]->getState() == RoomState::Alive)
				currentRoom->doors[startClose].doorAnimation->playReverse = true;
		}
	}
	if (currentMap->done) {
		if (!transitionGoing) {
			currentRoom->Update();
			currentMap->playerX = currentRoom->pos.x;
			currentMap->playerY = currentRoom->pos.y;
			for (int doorsChecked = 0; doorsChecked < 4; doorsChecked++) {
				if (currentRoom->doors[doorsChecked].entered) {
					transitionGoing = true;
					doorToDestRoom = doorsChecked;
					destRoom = currentRoom->neighbors[doorsChecked];
					transitionTime = 0;
					gameCore->EndUpdateHere();
					return;
				}
			}
		}
		else if (transitionTime < 15) {
			transitionTime++;
			gameCore->EndUpdateHere();
			return;
		}
		else {
			for (int doorToDestRoom = 0; doorToDestRoom < 4; doorToDestRoom++) {
				gameCore->deleteObject(currentRoom->doors[doorToDestRoom].id);
			}
			if (doorToDestRoom == 0 || doorToDestRoom == 2)
				player->setPosition(Vector2f(currentRoom->oppositeDoorPosition(doorToDestRoom).x, player->pos.y));
			if (doorToDestRoom == 1 || doorToDestRoom == 3)
				player->setPosition(Vector2f(player->pos.x, currentRoom->oppositeDoorPosition(doorToDestRoom).y));
			InitalizeRoom(destRoom->pos.x, destRoom->pos.y);
			transitionGoing = false;
		}
	}
}

void GameManager::InitalizeRoom(int x, int y) {
	currentRoom = &currentMap->roomMap[x][y];
	for (int ways = 0; ways < 4; ways++) {
		int neighborX = 0; int neighborY = 0;
		switch (ways) {
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
		currentRoom->neighbors[ways] = &currentMap->roomMap[neighborX][neighborY];
	}
	currentRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
	currentRoom->PlaceDoors(&gameCore->spriteSheet);
	for (int i = 0; i < 4; i++) {
		if (currentRoom->neighbors[i]->getState() == RoomState::Alive) {
			gameCore->addObject(&currentRoom->doors[i]);
		}
	}
}

void GameManager::Render(RenderWindow* window) {
	if (!initalized) return;
	window->setView(gameView);
	if (currentMap->done) {
		if(!transitionGoing)
		currentRoom->Render(window);
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
}