#include "Projectile.hpp"

Projectile::Projectile(sf::Vector2f& position, sf::Vector2f& direction, float speed, ProjectileType type) {
	this->position = position;
	this->direction = direction;
	this->speed = speed;
	this->type = type;
}
sf::Vector2f& Projectile::getPosition() {
	return position;
}
sf::Vector2f& Projectile::getDirection() {
	return direction;
}
float Projectile::getSpeed() {
	return speed;
}
ProjectileType Projectile::getType() {
	return type;
}
void Projectile::setPosition(sf::Vector2f& position) {
	this->position = position;
}
void Projectile::setDirection(sf::Vector2f& direction) {
	this->direction = direction;
}
void Projectile::setSpeed(float speed) {
	this->speed = speed;
}
void Projectile::update(float delta) {
	position += direction * speed * delta;
}
void Projectile::draw(sf::RenderWindow& screen) {

}