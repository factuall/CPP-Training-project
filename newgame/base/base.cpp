#include "Object.h"
#include "base.h"

const int objLimit = 100;
Object* Objects[objLimit] = {};

void init() {
    for (int i = 0; i < objLimit; i++) {
        Objects[i] = new Object();
    }
}

void addObject(Object newObject) {
    for (int i = 0; i < objLimit; i++) {
        if (Objects[i]->isNull) {
            newObject.id = i;
            *Objects[i] = newObject;
            return;
        }
    }
}

Object* getObject(int id) {
    return Objects[id];
}

int getObjLimit() {
    return objLimit;
}