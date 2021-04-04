#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"


namespace fc {
	using namespace sf;

	class Collision {
	public:
		float distance(sf::Vector2f A, sf::Vector2f B);
		Vector2f normalize(Vector2f source);
		Collider* colliderA;
		Collider* colliderB;
		bool colliding;
		Vector2f velocityA;
		Vector2f diffVector;
		Vector2f adaptedPosition;
		Vector2f adaptedVelocity;
		Collision(Collider* cA, Collider* cB);
		void ProcessCollision(Collider* cA, Collider* cB) {

		};
		void adaptCollider(Vector2f velocity);
	private:
		//void pointCircle(Vector2f point, Vector2f circle, int radius);
		void BoxBox();
		void CircleCircle();
		void LineLine();
		
		void BoxCircle();
		void LineBox();
		void LineCircle();
		//void getCollisionDetails(Vector2f* result[2]);
	};

}
/*
if (!((abs(destVector.x) > sqSize) || (abs(destVector.y) > sqSize))) {
			if (abs(destVector.x) > abs(destVector.y)) {
				destVector.y *= ((abs(destVector.x) + abs(velocity.x)) / sqSize);
				destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
			}
			else if (abs(destVector.x) < abs(destVector.y)) {
				destVector.x *= ((abs(destVector.y) + abs(velocity.y)) / sqSize);
				destVector.y = (sqSize) * ((destVector.y < 0) ? -1 : 1);
			}
			else { //rare corner collision
				destVector.x = (sqSize) * ((destVector.x < 0) ? -1 : 1);
				destVector.y = (sqSize) * ((destVector.x < 0) ? -1 : 1);
			}

*/