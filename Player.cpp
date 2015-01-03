#include "Player.hpp"
#include <cmath>

void Player::init() {
	loadTexture("player.png");
}
void Player::update(float delta) {
	// simulate movement here - using  a direction vector
	move(delta);
	setSpeed(getSpeed() * (0.999f - delta));
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
void Player::restrictToBounds(float x, float y, float width, float height) {
	if (getPosition().x > x + width)	getPosition().x = x;
	if (getPosition().x < x)			getPosition().x = x + width;
	if (getPosition().y > y + width)	getPosition().y = y;
	if (getPosition().y < y)			getPosition().y = y + width;
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