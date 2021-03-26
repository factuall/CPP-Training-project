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

sf::Font fontRegular;
sf::Font fontShadow;

sf::Image imageSheet;
sf::Texture sheet;

sf::RenderWindow window(sf::VideoMode(1024, 576), "tboifg - factuall", sf::Style::Close);
int lastTick, deltaTime; 
int lastTime = 0; double deltaTIme;
double PCFreq = 0.0;
__int64 CounterStart = 0;
Object fpsDisplay;

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

void update() {
    for (int updatedObject = 0; updatedObject < getObjLimit(); updatedObject++) {
        Object *currentObject = getObject(updatedObject);
        if (!(currentObject->isNull)) {
            currentObject->Update();
            if (currentObject->isCollider) {
                //collision detection between objects
                for (int collisionObject = 0; collisionObject < getObjLimit(); collisionObject++) {
                    Object* collidedObject = getObject(collisionObject);
                    if (!(collidedObject->isNull) && collisionObject != updatedObject && collidedObject->isCollider) {
                        if (currentObject->x < collidedObject->x + collidedObject->sizeX &&
                            currentObject->x + currentObject->sizeX > collidedObject->x &&
                            currentObject->y < collidedObject->y + collidedObject->sizeY &&
                            currentObject->y + currentObject->sizeY > collidedObject->y) {
                            // collision detected!
                            currentObject->OnColision(collidedObject);
                        }
                    }
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
            switch (currentObject->type) {
                case GameObject: {
                    currentObject->sprite.setPosition(currentObject->x, currentObject->y);
                    window.draw(currentObject->sprite);
                    break;
                }
                case TextObject: {
                    currentObject->text.setPosition(currentObject->x, currentObject->y);
                    window.draw(currentObject->text);
                }
            }

        }
    }
    window.display();
}

int main()
{
    if (!fontRegular.loadFromFile("../Release/fonts/suture.ttf"))
    {
        // error...
        printf("error while loading font\n");
        return 0;
    }
    if (!fontShadow.loadFromFile("../Release/fonts/future.ttf"))
    {
        // error...
        printf("error while loading font\n");
        return 0;
    }
    if (!imageSheet.loadFromFile("../Release/img/sheet.png"))
    {
        // error...
        printf("error while loading font\n");
        return 0;
    }
    imageSheet.createMaskFromColor(sf::Color(255, 0, 255, 255));
    sheet.loadFromImage(imageSheet);
    StartTimer();   
    init();

    fpsDisplay = Object(0, 0);
    fpsDisplay.type = TextObject;
    sf::Text fpsText;
    fpsText.setFont(fontRegular);
    fpsText.setString(std::to_string(framesPerSecond));
    fpsText.setCharacterSize(32); // in pixels, not points!
    fpsText.setFillColor(sf::Color::White);
    fpsDisplay.text = fpsText;
    addObject(&fpsDisplay); 

    Player testObject = Player(32, 32);
    testObject.type = GameObject;
    sf::Sprite testSprite(sheet, sf::IntRect(0, 0, 32, 32));
    testSprite.scale(2, 2);
    testObject.sprite = testSprite;
    addObject(&testObject);

    Object asd = Object(100, 64);
    asd.type = GameObject;
    asd.isCollider = true;
    sf::Sprite asdSprite(sheet, sf::IntRect(32, 0, 32, 32));
    asdSprite.scale(2, 2);
    asd.sprite = asdSprite;
    addObject(&asd);
    


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