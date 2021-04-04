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
		void BoxBox();
		void CircleCircle();
		void LineLine();
		
		void CircleBox();
		void LineBox();
		void LineCircle();
	};

}
