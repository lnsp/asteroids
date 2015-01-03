#include "Player.hpp"
#include <cmath>

void Player::init() {
	loadTexture("player.png");
}
void Player::update(float delta) {
	// simulate movement here - using  a direction vector
	getPosition() += delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
	setSpeed(getSpeed() * (0.999f - delta));
}
void Player::accelerate(float amount) {
	// accelerate spaceship
	setSpeed((getSpeed() + 0.5f) * amount);
	if (getSpeed() > MAX_SPEED) setSpeed(MAX_SPEED);
}
void Player::rotateLeft(float delta) {
	// rotate faster when more speed
	rotate((-40 - getSpeed() / 2) * delta);
}
void Player::rotateRight(float delta) {
	// rotate faster when more speed
	rotate((40 + getSpeed() / 2) * delta);
}
void Player::restrictToBounds(int x, int y, int width, int height) {
	if (getPosition().x > x + width)	getPosition().x = x;
	if (getPosition().x < x)			getPosition().x = x + width;
	if (getPosition().y > y + width)	getPosition().y = y;
	if (getPosition().y < y)			getPosition().y = y + width;
}