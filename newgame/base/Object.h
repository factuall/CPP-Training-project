#pragma once

class Object {
public:
    int x, y, id;
    bool isNull = true;
    Object(int nX, int nY, int nID);
    Object();
    void Move(int mX, int mY);
    void setPosition(int mX, int mY);
}; 
