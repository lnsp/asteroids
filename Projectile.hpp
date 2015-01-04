#include "Entity.hpp"
#include "Meteor.hpp"
#pragma once

class Projectile : public Entity {
	static const float MAX_LIFETIME;
	float lifetime;
	void init();
public:
	Projectile(sf::Vector2f& position) : Entity(position) { init(); };
	Projectile() : Entity() { init(); };
	bool update(float delta, std::vector<Meteor>& meteors);
	void draw(sf::RenderWindow& screen);
};