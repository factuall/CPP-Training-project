
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
	void Collision::LineLine() {

	}
	void Collision::BoxCircle() {
		Vector2f temp = colliderB->pos;
		if (colliderB->pos.x < colliderA->pos.x)         temp.x = colliderA->pos.x;						// test left edge
		else if (colliderB->pos.x > colliderA->pos.x + colliderA->size.x) temp.x = colliderA->pos.x + colliderA->size.x;   // right edge
		if (colliderB->pos.y < colliderA->pos.y)         temp.y = colliderA->pos.y;						// top edge
		else if (colliderB->pos.y > colliderA->pos.y + colliderA->size.y) temp.y = colliderA->pos.y + colliderA->size.y; // bottom edge
		//is distance from closest edge smaller than circle radius
		entryPos.x = colliderA->pos.x; entryPos.y = colliderA->pos.y;
		diffVector.x = (colliderA->pos.x - colliderB->pos.x); diffVector.y = (colliderA->pos.y - colliderB->pos.y);
		colliding = (distance(colliderB->pos, temp) <= colliderB->size.x);
		
	}
	void Collision::LineBox() {
		/*Collider up(colliderB->pos, operator+(colliderB->pos, colliderB->size), ColliderType::LineType),
			down(colliderB->pos, operator+(colliderB->pos, colliderB->size), ColliderType::LineType),
			left(colliderB->pos.x, colliderB->pos.y, colliderB->pos.x, colliderB->pos.y + colliderB->size.y),
			right(colliderB->pos.x + colliderB->size.x, colliderB->pos.y, colliderB->pos.x + colliderB->size.x, colliderB->pos.y + colliderB->size.y);
		entryPos = Vector2f();
		posDiffVector = Vector2f();
		if (lineLine(A, &up, &entryPos)) {
			lineLine(A, &down, &posDiffVector);
			lineLine(A, &left, &posDiffVector);
			lineLine(A, &right, &posDiffVector);
		}
		else if (lineLine(A, &down, &entryPos)) {
			lineLine(A, &up, &posDiffVector);
			lineLine(A, &left, &posDiffVector);
			lineLine(A, &right, &posDiffVector);
		}
		else if (lineLine(A, &left, &entryPos)) {
			lineLine(A, &up, &posDiffVector);
			lineLine(A, &down, &posDiffVector);
			lineLine(A, &right, &posDiffVector);
		}
		else if (lineLine(A, &right, &entryPos)) {
			lineLine(A, &up, &posDiffVector);
			lineLine(A, &left, &posDiffVector);
			lineLine(A, &down, &posDiffVector);
		}
		return (lineLine(A, &up) || lineLine(A, &down) || lineLine(A, &left) || lineLine(A, &right));*/
	}
	void Collision::LineCircle() {
		/*LineCollider* A = dynamic_cast<LineCollider*>(colliderA);
		CircleCollider* B = dynamic_cast<CircleCollider*>(colliderB);
		//line start or destination in circle
		if (pointCircle(A->pos, B->pos, B->size.x) ||
			pointCircle(A->dest, B->pos, B->size.x)) {
			entryPos = Vector2f(A->pos.x, A->pos.y);
			posDiffVector = Vector2f(B->pos.x, B->pos.y);
			return true;
		}
		float lineLength = distance(A->pos, A->dest);
		float dot = (((B->pos.x - A->pos.x) * (A->dest.x - A->pos.x)) + ((B->pos.y - A->pos.y) * (A->dest.y - A->pos.y))) / pow(lineLength, 2);
		Vector2f closest = Vector2f(
			A->pos.x + (dot * (A->dest.x - A->pos.x)),
			A->pos.y + (dot * (A->dest.y - A->pos.y))
		);
		//is closest point on the line
		if (!linePoint(A->pos, A->dest, closest)) {

			return false;
		}
		//if closest point in circle
		entryPos = Vector2f(B->pos.x, B->pos.y);
		posDiffVector = closest;
		if (distance(closest, B->pos) <= B->size.x) return  true;

		*/
	}


}
