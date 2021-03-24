#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Object.h"
//#include "base.h"
#include <stdlib.h>
#include <Windows.h>
#include <chrono>
#include <time.h>

//ASD
sf::RenderWindow window(sf::VideoMode(1024, 576), "kozakpolv");
int lastTick, deltaTime;
int lastTime; double deltaTIme;
double PCFreq = 0.0;
__int64 CounterStart = 0;

/*


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
    deltaTime = (int)now - lastTime;
    lastTime = (int)now;
    return deltaTime;

}

int ticks = 0;
const int predictionLength = 2147483646;
void update() {
    Sleep(100);
    if (ticks > 10) {
        ticks = 0;

    }
    else {
        ticks++;
    }

}

void render() {

    window.clear();
    for (int displayedObj = 0; displayedObj < getObjLimit(); displayedObj++) {
        Object* currentObject = getObject(displayedObj);
        if (!(currentObject->isNull)) {
            std::cout << currentObject->isNull << std::endl;
            sf::RectangleShape objShape(sf::Vector2f(64, 64));
            objShape.setPosition((currentObject->x), (currentObject->y));
            objShape.setFillColor(sf::Color(155, 155, 155, 255));
            window.draw(objShape);
        }
    }
    window.display();
}
*/
int main()
{
  /*
    StartTimer();

    init();
    for (int i = 0; i < 100; i++) {
        addObject(Object(i * 8, 32, 0));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        update();
        render();



    }
    */
    return 0;
}