#include "Entity.hpp"
#pragma once

class Projectile : public Entity {
	void init();
public:
	Projectile(sf::Vector2f& position) : Entity(position) {};
	Projectile() : Entity() { init(); };
	void update(float delta);
};