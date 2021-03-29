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
	sf::Vector2f entryPos, posDiffVector;

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
	void UpdateCollision() {
		ProcessCollision(colliderA, colliderB);
	}

	static float distance(sf::Vector2f A, sf::Vector2f B);
	static sf::Vector2f normalize(sf::Vector2f source);
private:
	bool pointCircle(sf::Vector2f point, sf::Vector2f circle, int radius);
	bool linePoint(sf::Vector2f linePos, sf::Vector2f lineDest, sf::Vector2f point);
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
