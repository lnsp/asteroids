#include "Entity.hpp"
#include "ResourceManager.hpp"

extern ResourceManager resourceManager;

Entity::Entity(sf::Vector2f& position) {
	this->position = position;
}
void Entity::move(float delta) {
	getPosition() += delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
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
void Entity::loadTexture(std::string file) {
	texture = resourceManager.get(file);
	shape.setTexture(*texture);
	shape.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
}