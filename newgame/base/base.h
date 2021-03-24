#pragma once
#include "Object.h"
extern const int objLimit;
extern Object* Objects[];
void init();
void addObject(Object newObject);
Object* getObject(int id);
int getObjLimit();