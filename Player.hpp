#include <vector>
#include "Entity.hpp"
#include "Projectile.hpp"
#pragma once

class Player : public Entity {
	const float MAX_SPEED = 300.0f, PROJECTILE_RATE = 0.25f;
	bool shotLeft = false;
	sf::Time lastProjectile;
	void init();
public:
	Player(sf::Vector2f& position) : Entity(position) { init(); };
	Player() : Entity() { init(); };
	void update(float delta);
	void accelerate(float amount);
	void rotateLeft(float delta);
	void rotateRight(float delta);
	void restrictToBounds(float x, float y, float width, float height);
	void shoot(std::vector<Projectile>& gameProjectiles, sf::Time& gameTime);
};