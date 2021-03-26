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
	Collision();
	//basic
	Collision(BoxCollider *A, BoxCollider *B);
	Collision(CircleCollider *A, CircleCollider *B);
	Collision(LineCollider *A, LineCollider *B);

	//box-circle
	Collision(BoxCollider *A, CircleCollider *B);
	Collision(CircleCollider* A, BoxCollider* B) : Collision(B, A) {};

	//box-line
	Collision(LineCollider* A, BoxCollider* B);
	Collision(BoxCollider* A, LineCollider* B) : Collision(B, A) {};

	//line-circle
	Collision(LineCollider *A, CircleCollider *B);
	Collision(CircleCollider *A, LineCollider *B) : Collision(B, A) {};

	void getCollisionDetails(sf::Vector2f* result[2]);
	
private:
	float distance(int x, int y, int destX, int destY);
	bool pointCircle(int x, int y, int circleX, int circleY, int radius);
	bool linePoint(int x, int y, int destX, int destY, int pointX, int pointY);
	bool lineLine(LineCollider* A, LineCollider* B, sf::Vector2f* intersection);
	bool lineLine(LineCollider* A, LineCollider* B);
	sf::Vector2f entryPoint, relativePoint;

};
