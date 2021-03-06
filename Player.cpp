#include "Player.hpp"
#include <cmath>

void Player::init() {
	loadTexture("player.png");
}
bool Player::isDead() {
	return dead;
}
int Player::getMaxHP() {
	return MAX_HP;
}
int Player::getHP() {
	return hp;
}
void Player::resetHP() {
	hp = MAX_HP;
	dead = false;
}
void Player::update(float delta, std::vector<Meteor>& meteors) {
	// simulate movement here - using  a direction vector
	move(delta);
	setSpeed(getSpeed() * (0.999f - delta));

	for (auto it = meteors.begin(); it != meteors.end(); ++it) {
		if (it->getBoundingBox().intersects(getBoundingBox())) {
			if (--hp <= 0) {
				dead = true;
			}
			meteors.erase(it);
			break;
		}
	}
}
void Player::accelerate(float amount) {
	// accelerate spaceship
	setSpeed((getSpeed() + 0.5f) * amount);
	if (getSpeed() > MAX_SPEED) setSpeed(MAX_SPEED);
}
void Player::rotateLeft(float delta) {
	// rotate faster when more speed
	rotate((-40) * delta);
}
void Player::rotateRight(float delta) {
	// rotate faster when more speed
	rotate((40) * delta);
}
void Player::shoot(std::vector<Projectile> &gameProjectiles, sf::Time &gameTime) {
	sf::Time distanceTime = gameTime - lastProjectile;

	if (distanceTime.asSeconds() > PROJECTILE_RATE) {
		lastProjectile = gameTime;

		// get angles and position from player
		float projectileAngle = getRotation();
		sf::Vector2f projectilePosition = getPosition();

		// calculating transformation for realistic fire
		float shotAngle = (projectileAngle - 90 * (shotLeft * 2 - 1));
		float shotTranslationX = cos(shotAngle * 3.14f / 180) * 30;
		float shotTranslationY = sin(shotAngle * 3.14f / 180) * 30;

		// applying the transformation
		projectilePosition.x += shotTranslationX;
		projectilePosition.y += shotTranslationY;

		// create the projectile
		Projectile projectile{ projectilePosition };
		projectile.setSpeed(MAX_SPEED * 3);
		projectile.setRotation(projectileAngle);

		// switch fire sides
		shotLeft = !shotLeft;

		// append the projectile to the vector
		gameProjectiles.push_back(projectile);
	}
}