#include "Entity.hpp"
#pragma once

class Player : public Entity {
	void init();
public:
	Player(sf::Vector2f& position) : Entity(position) { init(); };
	Player() : Entity() { init(); };
	void update(float delta);
	void accelerate(float amount);
	void rotateLeft(float delta);
	void rotateRight(float delta);
};