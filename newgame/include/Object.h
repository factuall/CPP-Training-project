#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Collider.h"
#include "Collision.h"
namespace fc {
	using namespace sf;
	class Object {
	public:
		int id;
		sf::Vector2f pos = sf::Vector2f();
		int sizeX = 64, sizeY = 64;
		bool isNull = true, isVisible = false;

		Object(int nX, int nY);
		Object();

		void Move(sf::Vector2f mPos);
		void setPosition(sf::Vector2f nPos);

		virtual void Update();
		virtual void Render(sf::RenderWindow* window);
		virtual void OnCollision(Collision collision);

		sf::Text text;
		sf::Sprite sprite;

		Collider* collider;
		Collider* getCollider();
		bool isTrigger = false;
		sf::Vector2f spriteScale();
	private:
	};
}
