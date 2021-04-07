#include "GameManager.h"
#include <iostream>

using namespace sf;
using namespace fc;
GameManager::GameManager(Text txt, Core* gameCore) {
	//object
	id = 0;
	isNull = false;
	isVisible = true;
	isTrigger = false;
	this->gameCore = gameCore;
	collider = new Collider(Vector2f(-21, -37), Vector2f(0, 0));
	//map
	currentMap = new GameFloor(txt);
	gameCore->addObject(currentMap);
	currentMap->Start();
	//player
	player = new Player(560, 340, &gameCore->spriteSheet);
	gameCore->addObject(player);
};

int generationTime = 0; int transitionTime = 0;
void GameManager::Update() {
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
		if (!transitionPlaying) {
			currentRoom->Update();
			currentMap->playerX = currentRoom->pos.x;
			currentMap->playerY = currentRoom->pos.y;
			for (int doorsChecked = 0; doorsChecked < 4; doorsChecked++) {
				if (currentRoom->doors[doorsChecked].entered) {
					transitionRoom = nullptr;
					transitionPlaying = true;
					InitTransitionRoom(currentRoom->neighbors[doorsChecked]->pos.x, currentRoom->neighbors[doorsChecked]->pos.y,
					currentRoom->neighbors[doorsChecked]->pos - currentRoom->pos);
					transitionTime = 0;
					return;



				}
			}
		}
		else {
			if (transitionTime < 30) {
				windowView.move((transitionRoom->sprite.getPosition() + Vector2f(512.f,288.f) - windowView.getCenter()) / 4.5f);
				transitionTime++;
			}
			else {
				windowView = sf::View(Vector2f(512.f, 288.f), Vector2f(1024.f, 576.f));
				for (int doorsChecked = 0; doorsChecked < 4; doorsChecked++) {
					if (currentRoom->doors[doorsChecked].entered) {
						
						transitionTime = 0;
						if (doorsChecked == 0 || doorsChecked == 2)
							player->setPosition(Vector2f(currentRoom->oppositeDoorPosition(doorsChecked).x, player->pos.y));
						if (doorsChecked == 1 || doorsChecked == 3)
							player->setPosition(Vector2f(player->pos.x, currentRoom->oppositeDoorPosition(doorsChecked).y));
						for (int doorsToDelete = 0; doorsToDelete < 4; doorsToDelete++) {
							gameCore->deleteObject(currentRoom->doors[doorsChecked].id);
						}
						InitalizeRoom(currentRoom->neighbors[doorsChecked]->pos.x, currentRoom->neighbors[doorsChecked]->pos.y);
						for (int doorsToDelete = 0; doorsToDelete < 4; doorsToDelete++) {
							gameCore->deleteObject(transitionRoom->doors[doorsChecked].id);

						}
						transitionPlaying = false;

					}
				}

			}
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
void GameManager::InitTransitionRoom(int x, int y, Vector2f newRoom) {
	transitionRoom = &currentMap->roomMap[x][y];
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
		transitionRoom->neighbors[ways] = &currentMap->roomMap[neighborX][neighborY];
	}
	
	std::cout << newRoom.x * 1024 << " " << newRoom.y * 576 <<"\n";
	transitionRoom->sprite = sf::Sprite(gameCore->spriteSheet, sf::IntRect(0, 736, 512, 288));
	transitionRoom->sprite.setPosition( + newRoom.x * 1024, currentRoom->pos.y + newRoom.y * 576);
	for (int ways = 0; ways < 4; ways++) {
		if (transitionRoom->neighbors[ways]->getState() == RoomState::Alive) {
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
			transitionRoom->doors[ways] = Door(x + transitionRoom->sprite.getPosition().x, y + transitionRoom->sprite.getPosition().y, offX, offY, &gameCore->spriteSheet);
			transitionRoom->doors[ways].angle = 450 - (ways * 90);
			transitionRoom->doors[ways].open = true;
		}
		for (int i = 0; i < 4; i++) {
			if (transitionRoom->neighbors[i]->getState() == RoomState::Alive) {
				gameCore->addObject(&currentRoom->doors[i]);
				
			}
		}
	}

	
}

void GameManager::Render(RenderWindow* window) {
	if (currentMap->done) {
		currentRoom->Render(window);
		if (transitionPlaying) {
			transitionRoom->Render(window);
			for (int i = 0; i < 4; i++) {
				if (transitionRoom->neighbors[i]->getState() == RoomState::Alive) {

					transitionRoom->doors[i].ManagedRender(window);
				}
			}
		}
	}
	currentMap->ManagedRender(window);
	player->ManagedRender(window);
	window->setView(windowView);
	
}