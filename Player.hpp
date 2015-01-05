#include <vector>
#include "Entity.hpp"
#include "Projectile.hpp"
#pragma once

class Player : public Entity {
	const float MAX_SPEED		= 300.0f;
	const float PROJECTILE_RATE = 0.25f;
	bool shotLeft				= false;
	const int MAX_HP			= 3;
	int hp						= MAX_HP;
	bool dead = true;
	sf::Time lastProjectile;
	void init();
public:
	Player(sf::Vector2f& position) : Entity(position) { init(); };
	Player() : Entity() { init(); };
	int getHP();
	void resetHP();
	int getMaxHP();
	bool isDead();
	void update(float delta, std::vector<Meteor>& meteors);
	void accelerate(float amount);
	void rotateLeft(float delta);
	void rotateRight(float delta);
	void shoot(std::vector<Projectile>& gameProjectiles, sf::Time& gameTime);
};