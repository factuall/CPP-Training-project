#include "Core.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <chrono>

namespace fc {
	Core::Core(Image* img, Font* fnt, Font* altFnt) {
		window = new RenderWindow(VideoMode(1024, 576), "thboi - factuall", Style::Close);
		image = *img;
		fontRegular = *fnt;
		fontAlternative = *altFnt;
		image.createMaskFromColor(Color(255, 0, 255, 255));
		spriteSheet.loadFromImage(image);
		for (int i = 0; i < objLimit; i++) {
			Objects[i] = new Object();
		}
	}

	void Core::run() {
		//start timer
	}

	Object* Core::getObject(int id) {
		return Objects[id];
	}

	void Core::addObject(Object* newObject) {
		for (int i = 0; i < objLimit; i++) {
			if (Objects[i]->isNull) {
				newObject->id = i;
				Objects[i] = newObject;
				return;
			}
		}
	}

	void Core::deleteObject(int id)
	{
		Objects[id] = new Object();
		Objects[id]->isNull = true;
	}

	void Core::render() {
		window->clear();
			for (int displayedObj = 0; displayedObj < objLimit; displayedObj++) {

					if (!(Objects[displayedObj]->isNull) && Objects[displayedObj]->isVisible) {
						Objects[displayedObj]->Render(window);
					}
				
			}
		
		window->display();
	}

	void Core::update() {
		for (int id = 0; id < objLimit; id++) {
			if (Objects[id]->isNull) continue;
			Objects[id]->Update();
			if (Objects[id]->collider->active && Objects[id]->isTrigger) {
				for (int checkedId = 0; checkedId < objLimit; checkedId++) {
					if (Objects[checkedId]->isNull ||
						!(Objects[checkedId]->collider->active) ||
						checkedId == id) continue;
					Collision col(Objects[id]->collider, Objects[checkedId]->collider);

					if (col.colliding) {
						Objects[id]->OnCollision(col);
					}
				}
			}
		}
	}
}