#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <chrono>
#include <time.h>

#include "base/Object.h"
#include "base/Collision.h"
#include "base/Collider.h"
#include "base/BoxCollider.h"
#include "base/base.h"

#include "Player.h"
#include "FPSDisplay.h"

sf::Font fontRegular;
sf::Font fontShadow;

sf::Image imageSheet;
sf::Texture sheet;

sf::RenderWindow window(sf::VideoMode(1024, 576), "tboifg - factuall", sf::Style::Close);


int lastTick, deltaTime; 
int lastTime = 0; double deltaTIme;
double PCFreq = 0.0;
__int64 CounterStart = 0;

FPSDisplay fpsDisplay;

void StartTimer()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 100000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;

}
int RelativeTime()
{

    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq / 100.0;
}
int SystemTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart) / PCFreq / 100.0;
}
int DeltaTime()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    double now = (double(li.QuadPart) / PCFreq) / 100.0;
    if (lastTime == 0) lastTime = (int)now;
    deltaTime = (int)now - lastTime;
    lastTime = (int)now;
    return deltaTime;

}

sf::Vector2f plx;
sf::Vector2f clx;

void update() {
    for (int id = 0; id < getObjLimit(); id++) {
        if (getObject(id)->isNull) continue;
        Object *updatedObj = getObject(id);
        updatedObj->Update();
        if (updatedObj->collider->active && updatedObj->isTrigger) {
            for (int checkedId = 0; checkedId < getObjLimit(); checkedId++) {
                if (getObject(checkedId)->isNull ||
                    !(getObject(checkedId)->collider->active) ||
                    checkedId == id) continue;
                    Collision col(updatedObj->collider, getObject(checkedId)->collider);
                    if (col.distance(sf::Vector2f(0, 0), col.relPos) < 128) {
                        updatedObj->OnCollision(col);
                    }

            }
        }
    }
}


int skipTickTime = 0, secondCounter = 0, framesInSecond = 0, framesPerSecond = 0;
void render() {
    fpsDisplay.text.setString(std::to_string(framesPerSecond));
    window.clear();
    for (int displayedObj = 0; displayedObj < getObjLimit(); displayedObj++) {
        Object* currentObject = getObject(displayedObj);
        if (!(currentObject->isNull) && currentObject->isVisible) {
             
            currentObject->Render(&window);
        }
    }
    window.display();
}

int main()
{
    if (!fontRegular.loadFromFile("../Release/fonts/suture.ttf") ||
        !fontShadow.loadFromFile("../Release/fonts/future.ttf") ||
        !imageSheet.loadFromFile("../Release/img/sheet.png"))
    {
        printf("error while loading resources\n");
        return 0;
    }
    imageSheet.createMaskFromColor(sf::Color(255, 0, 255, 255));
    sheet.loadFromImage(imageSheet);
    StartTimer();   
    init();

    Player playerObj = Player(300, 300);
    playerObj.sprite = sf::Sprite(sheet, sf::IntRect(0, 0, 32, 32));
    addObject(&playerObj);

    Object Wall = Object(128, 128);
    Wall.sprite = sf::Sprite(sheet, sf::IntRect(0, 32, 32, 32));
    Wall.collider = new BoxCollider(Wall.x, Wall.y, 64, 64);
    Wall.isVisible = true;
    addObject(&Wall);
    
    fpsDisplay = FPSDisplay();
    fpsDisplay.text.setFont(fontRegular);
    fpsDisplay.text.setString(std::to_string(framesPerSecond));
    addObject(&fpsDisplay);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //limit update rate to 60
        if (DeltaTime() <= 16 && skipTickTime < 16) {
            skipTickTime += deltaTime;
        }
        secondCounter += deltaTime;
        if (secondCounter >= 1000) {
            framesPerSecond = framesInSecond;
            framesInSecond = 0;
            secondCounter = 0;
        }
        if (skipTickTime >= 16) {
            skipTickTime = 0;
            framesInSecond++;
            update();
        }
        render();
    }
    return 0;
}