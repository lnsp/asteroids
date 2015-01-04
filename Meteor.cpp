#include "Meteor.hpp"

sf::Time Meteor::lastMeteorSpawn;
float Meteor::spawning_rate = 3.0f;

void Meteor::init() {
	loadTexture("meteor_big.png");
}

void Meteor::update(float delta) {
	move(delta);
}
void Meteor::spawn(std::vector<Meteor>& gameMeteors, sf::Vector2f& playerPosition, sf::Time& gameTime, float radius) {
	sf::Time distanceTime = gameTime - Meteor::lastMeteorSpawn;
	
	if (distanceTime.asSeconds() > 2) {
		Meteor::lastMeteorSpawn = gameTime;

		// generate random position outside the window
		float angle = rand() % 360 * 180 / 3.14f;
		sf::Vector2f meteorPosition{ cos(angle) * radius + playerPosition.x, sin(angle) * radius + playerPosition.y};

		// calculate direction to throw it to the player
		sf::Vector2f direction = playerPosition - meteorPosition;

		// vector to angle
		float rotation = atan2(direction.y, direction.x) * 180 / 3.14f;

		// create object and append it to the vector
		Meteor m{ meteorPosition };

		// generate random speed between 150 and 199
		m.setSpeed(rand() % 50 + 50);
		m.setRotation(rotation);
		gameMeteors.push_back(m);

		spawning_rate += 0.5f;
	}
}