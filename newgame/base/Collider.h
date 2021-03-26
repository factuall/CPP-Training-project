#pragma once

class Collider {
public:
	enum class ColliderType { BoxType, CircleType, LineType, PointType };
	int x, y;
	bool active = false;
	ColliderType type = Collider::ColliderType::PointType;
	virtual ~Collider();
};