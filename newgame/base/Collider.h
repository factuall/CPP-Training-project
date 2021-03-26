#pragma once
enum ColliderType { BoxType, CircleType, LineType };
class Collider {
public:
	int x, y;
	ColliderType type;
	virtual ~Collider();
};