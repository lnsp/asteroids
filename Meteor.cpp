#include "Meteor.hpp"

void Meteor::init() {
	loadTexture("meteor_big.png");
}

void Meteor::update(float delta) {
	getPosition() += delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
	/* ------------------------------------------------------------
			UNCOMMENT THIS FOR DRUNKEN METEORS
	---------------------------------------------------------------*/
	int sgn = getRotation() >= 0 ? 1 : -1;
	setRotation(getRotation() + delta * sgn * getSpeed() / 10);
}