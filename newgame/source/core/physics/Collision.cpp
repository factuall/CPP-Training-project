
#include "Collision.h"
#include <iostream>

namespace fc {
	float Collision::distance(sf::Vector2f A, sf::Vector2f B) {
		return sqrt(((A.x - B.x) * (A.x - B.x)) + ((A.y - B.y) * (A.y - B.y)));
	}
	Vector2f Collision::normalize(sf::Vector2f source) {
		float length = distance(sf::Vector2f(), source);
		if (length != 0)
			return sf::Vector2f(source.x / length, source.y / length);
		else
			return source;
	}

	Collision::Collision(Collider* A, Collider* B) {
		colliderA = A; colliderB = B;
		//Basic collisions
	//box-box
		if (colliderA->type == ColliderType::BoxType &&
			colliderB->type == ColliderType::BoxType) {
			BoxBox();
		}
		//circle-circle
		if (colliderA->type == ColliderType::CircleType &&
			colliderB->type == ColliderType::CircleType) {
			CircleCircle();
		}
		//line-line
		if (colliderA->type == ColliderType::LineType &&
			colliderB->type == ColliderType::LineType) {
			LineLine();
		}

		//Mixed collisions
	//box-circle && circle-box
		if (colliderA->type == ColliderType::BoxType &&
			colliderB->type == ColliderType::CircleType) {
			BoxCircle();
		}
		if (colliderA->type == ColliderType::CircleType &&
			colliderB->type == ColliderType::BoxType) {
			colliderA = B; colliderB = A; BoxCircle();
		}
		//line-box && box-line
		if (colliderA->type == ColliderType::LineType &&
			colliderB->type == ColliderType::BoxType) {
			LineBox();
		}
		if (colliderA->type == ColliderType::BoxType &&
			colliderB->type == ColliderType::LineType) {
			colliderA = B; colliderB = A; LineBox();
		}
		//line-circle && circle-line
		if (colliderA->type == ColliderType::LineType &&
			colliderB->type == ColliderType::CircleType) {
			LineCircle();
		}
		if (colliderA->type == ColliderType::CircleType &&
			colliderB->type == ColliderType::LineType) {
			colliderA = B; colliderB = A; LineCircle();
		}
	}

	/*	void Collision::LineLine() {
		//distances to intersection point
		float intersectionA =
			((B->dest.x - B->pos.x) * (A->pos.y - B->pos.y) - (B->dest.y - B->pos.y) * (A->pos.x - B->pos.x))
			/
			((B->dest.y - B->pos.y) * (A->dest.x - A->pos.x) - (B->dest.x - B->pos.x) * (A->dest.y - A->pos.y));
		float intersectionB =
			((A->dest.x - A->pos.x) * (A->pos.y - B->pos.y) - (A->dest.y - A->pos.y) * (A->pos.x - B->pos.x))
			/
			((B->dest.y - B->pos.y) * (A->dest.x - A->pos.x) - (B->dest.x - B->pos.x) * (A->dest.y - A->pos.y));

		//if distances between 0-1 lines are intersecting
		if (intersection != nullptr && (intersectionA >= 0 && intersectionA <= 1 && intersectionB >= 0 && intersectionB <= 1)) {
			*intersection = Vector2f(A->pos.x + (intersectionA * (A->dest.x - A->pos.x)), A->pos.y + (intersectionA * (A->dest.y - A->pos.y)));
			return true;
		}
		return (intersectionA >= 0 && intersectionA <= 1 && intersectionB >= 0 && intersectionB <= 1);
	}
*/
	void Collision::BoxBox() {
		diffVector.x = (colliderA->pos.x - colliderB->pos.x); diffVector.y = (colliderA->pos.y - colliderB->pos.y);
		colliding = (colliderA->pos.x < colliderB->pos.x + colliderB->size.x &&
			colliderA->pos.x + colliderA->size.x > colliderB->pos.x &&
			colliderA->pos.y < colliderB->pos.y + colliderB->size.y &&
			colliderA->pos.y + colliderA->size.y > colliderB->pos.y);
	}
	void Collision::CircleCircle() {
		colliding = (distance(colliderA->pos,colliderB->pos) <= ((colliderA->squareSize / 2)+ (colliderB->squareSize / 2)));
		diffVector.x = (colliderA->pos.x - colliderB->pos.x); diffVector.y = (colliderA->pos.y - colliderB->pos.y);
	}
	void Collision::LineLine() {}
	void Collision::BoxCircle() {
		Vector2f temp = colliderB->pos;
		if (colliderB->pos.x < colliderA->pos.x)         temp.x = colliderA->pos.x;						// test left edge
		else if (colliderB->pos.x > colliderA->pos.x + colliderA->size.x) temp.x = colliderA->pos.x + colliderA->size.x;   // right edge
		if (colliderB->pos.y < colliderA->pos.y)         temp.y = colliderA->pos.y;						// top edge
		else if (colliderB->pos.y > colliderA->pos.y + colliderA->size.y) temp.y = colliderA->pos.y + colliderA->size.y; // bottom edge
		//is distance from closest edge smaller than circle radius
		diffVector.x = (colliderA->pos.x - colliderB->pos.x); diffVector.y = (colliderA->pos.y - colliderB->pos.y);
		colliding = (distance(colliderB->pos, temp) <= colliderB->size.x);
		
	}
	void Collision::LineBox() {}
	void Collision::LineCircle() {}

	void Collision::adaptCollider(Vector2f velocity)
	{
		Vector2f destVector;
		if (colliderA->type == fc::ColliderType::BoxType && colliderB->type == fc::ColliderType::BoxType) {
			destVector = diffVector;
			int sqSize = colliderB->squareSize;
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
				adaptedPosition = colliderB->pos + destVector;
				adaptedVelocity = velocity;
				if (distance(Vector2f(), velocity) != 0) {
					if (abs(destVector.x) > abs(destVector.y)) {
						adaptedVelocity.x = 0;
					}
					else
						if (abs(destVector.x) < abs(destVector.y)) {
							adaptedVelocity.y = 0;
						}
						else { //rare corner collision
							adaptedVelocity = Vector2f();
						}
				}
			}
		}
	
		if (colliderA->type == fc::ColliderType::CircleType && colliderB->type == fc::ColliderType::CircleType) {
			destVector = diffVector;
			int sqSize = colliderB->squareSize;
			if (distance(colliderA->pos, colliderB->pos) < colliderA->squareSize + colliderB->squareSize) {
				while (distance(destVector + colliderA->pos, colliderB->pos) < colliderA->squareSize + colliderB->squareSize) {
					destVector.x = destVector.x * 1.01f;
					destVector.y = destVector.y * 1.01f;
				}

				adaptedPosition = (operator+(colliderB->pos, destVector));

				if (abs(velocity.x) > abs(velocity.y)) {
					velocity.y = abs(velocity.x) * ((destVector.y < 0) ? -1 : 1);
					velocity.x = abs((normalize(velocity).x) + (normalize(destVector).x)) * velocity.x;
				}
				else if (abs(velocity.x) < abs(velocity.y)) {
					velocity.x = abs(velocity.y) * ((destVector.x < 0) ? -1 : 1);
					velocity.y = abs((normalize(velocity).y) + (normalize(destVector).y)) * velocity.y;
				}
				else {

				}

				adaptedVelocity = velocity;

			}
		}
	
		
	}


}
