#include "Player.hpp"
#include <cmath>
#include "ResourceManager.hpp"

extern ResourceManager rm;

void Player::init() {
	texture = rm.get("player.png");
	shape.setTexture(*texture);
	shape.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void Player::update(float delta) {
	// simulate movement here - using  a direction vector
	getPosition() += delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
	setSpeed(getSpeed() * (0.999f - delta));
}
void Player::accelerate(float amount) {
	// accelerate spaceship
	setSpeed((getSpeed() + 0.5f) * amount);
}

void Player::rotateLeft(float delta) {
	rotate((-40 - getSpeed()) * delta);
}
void Player::rotateRight(float delta) {
	rotate((40 + getSpeed()) * delta);
}