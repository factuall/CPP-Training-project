#pragma once
#include <SFML/Graphics.hpp>
namespace fc {
	using namespace sf;
	enum class ColliderType { BoxType, CircleType, LineType };
	class Collider {
	public:
		Vector2f pos = Vector2f();
		Vector2f size = Vector2f();
		Vector2f offset = Vector2f();
		int squareSize;
		bool active = false; bool renderCollider = false;
		ColliderType type;
		Collider(Vector2f pos, Vector2f size);
		Collider(Vector2f pos, Vector2f size, Vector2f offset);
		Collider(Vector2f pos, Vector2f size, ColliderType type);
		void RenderCollider(sf::RenderWindow* window);
		char charTag = 'x';
	};
}
