#pragma once

#include <SFML/System.hpp>

#include "Collider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "LineCollider.h"
#include <vector>
class Collision {
public:
	Collider* colliderA;
	Collider* colliderB;
	bool colliding;
	sf::Vector2f entryPoint, relativePoint;

	Collision(Collider* cA, Collider* cB) {
		ProcessCollision(cA, cB);
	};

	void ProcessCollision(Collider* cA, Collider* cB) {
		colliderA = cA; colliderB = cB;

			//Basic collisions
		//box-box
		if (colliderA->type == Collider::ColliderType::BoxType &&
			colliderB->type == Collider::ColliderType::BoxType) {
			colliding = BoxBox();
		}
		//circle-circle
		if (colliderA->type == Collider::ColliderType::CircleType &&
			colliderB->type == Collider::ColliderType::CircleType) {
			colliding = CircleCircle();
		}
		//line-line
		if (colliderA->type == Collider::ColliderType::LineType &&
			colliderB->type == Collider::ColliderType::LineType) {
			colliding = LineLine();
		}

		
			//Mixed collisions
		//box-circle && circle-box
		if (colliderA->type == Collider::ColliderType::BoxType &&
			colliderB->type == Collider::ColliderType::CircleType) {
			colliding = BoxCircle();
		}
		if (colliderA->type == Collider::ColliderType::CircleType &&
			colliderB->type == Collider::ColliderType::BoxType) {
			colliderA = cB; colliderB = cA; colliding = BoxCircle();
		}
		//line-box && box-line
		if (colliderA->type == Collider::ColliderType::LineType &&
			colliderB->type == Collider::ColliderType::BoxType) {
			colliding = LineBox();
		}
		if (colliderA->type == Collider::ColliderType::BoxType &&
			colliderB->type == Collider::ColliderType::LineType) {
			colliderA = cB; colliderB = cA; colliding = LineBox();
		}	
		//line-circle && circle-line
		if (colliderA->type == Collider::ColliderType::LineType &&
			colliderB->type == Collider::ColliderType::CircleType) {
			colliding = LineCircle();
		}
		if (colliderA->type == Collider::ColliderType::CircleType &&
			colliderB->type == Collider::ColliderType::LineType) {
			colliderA = cB; colliderB = cA; colliding = LineCircle();
		}
	};



private:
	float distance(int x, int y, int destX, int destY);
	bool pointCircle(int x, int y, int circleX, int circleY, int radius);
	bool linePoint(int x, int y, int destX, int destY, int pointX, int pointY);
	bool lineLine(LineCollider* A, LineCollider* B, sf::Vector2f* intersection);
	bool lineLine(LineCollider* A, LineCollider* B);
	bool BoxBox();
	bool CircleCircle();
	bool LineLine();
	bool BoxCircle();
	bool LineBox();
	bool LineCircle();
	void getCollisionDetails(sf::Vector2f* result[2]);
};
