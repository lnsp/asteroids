#include "Entity.hpp"
#include <vector>
#pragma once

class Meteor : public Entity {
	void init();
	static sf::Time lastMeteorSpawn;
public:
	static float spawning_rate;
	Meteor(sf::Vector2f& position) : Entity(position) { init(); }
	Meteor() : Entity() { init(); };
	void update(float delta);
	static void spawn(std::vector<Meteor>& gameMeteors, sf::Vector2f& playerPosition, sf::Time& gameTime, float radius);
};