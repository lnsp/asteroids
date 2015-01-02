#include "Meteor.hpp"
#include "ResourceManager.hpp"

extern ResourceManager rm;

void Meteor::init() {
	texture = rm.get("meteor_big.png");
	shape.setTexture(*texture);
	shape.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void Meteor::update(float delta) {
	// simulate movement here - using  a direction vector
	getPosition() += delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
	
	/* calculate signum
	int sgn = getRotation() >= 0 ? 1 : -1;
	setRotation(getRotation() + delta * sgn * getSpeed() / 5);*/
}