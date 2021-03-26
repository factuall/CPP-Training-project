#pragma once
enum ColliderType { BoxType, CircleType };
class Collider {
public:
	int x, y;
	ColliderType type;
	virtual ~Collider();
};