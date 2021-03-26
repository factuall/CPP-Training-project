#pragma once

class Collider {
public:
	enum class ColliderType { BoxType, CircleType, LineType, PointType };
	int x, y;
	ColliderType type = Collider::ColliderType::PointType;
	virtual ~Collider();
};