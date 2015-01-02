#include "Entity.hpp"

Entity::Entity(sf::Vector2f& position) {
	this->position = position;
}
sf::Vector2f& Entity::getPosition() {
	return position;
}
float Entity::getRotation() {
	return rotation;
};
void Entity::setPosition(sf::Vector2f& position) {
	this->position = position;
}
void Entity::setRotation(float rotation) {
	this->rotation = rotation;
}
void Entity::draw(sf::RenderWindow& screen) {
	shape.setRotation(rotation);
	shape.setPosition(position);
	screen.draw(shape);
}
void Entity::rotate(float amount) {
	rotation += amount;
}
float Entity::getSpeed() {
	return speed;
}
void Entity::setSpeed(float speed) {
	this->speed = speed;
}