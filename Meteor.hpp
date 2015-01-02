#include "Entity.hpp"
#pragma once

class Meteor : public Entity {
	void init();
public:
	Meteor(sf::Vector2f& position) : Entity(position) { init(); }
	Meteor() : Entity() { init(); };
	void update(float delta);
};