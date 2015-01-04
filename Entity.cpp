#include "Entity.hpp"
#include "ResourceManager.hpp"

extern ResourceManager resourceManager;

Entity::Entity(sf::Vector2f& position) {
	this->position = position;
}
float Entity::move(float delta) {
	sf::Vector2f transformation = delta * getSpeed() * sf::Vector2f{ cos(getRotation() * 3.14159265359f / 180), sin(getRotation() * 3.14159265359f / 180) };
	getPosition() += transformation;

	return sqrt(pow(transformation.x, 2) + pow(transformation.y, 2));
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
void Entity::draw(sf::RenderWindow& screen, bool drawBoundingBox) {
	shape.setRotation(rotation);
	shape.setPosition(position);
	screen.draw(shape);

	if (drawBoundingBox) {
		sf::RectangleShape box{ sf::Vector2f(shape.getGlobalBounds().width, shape.getGlobalBounds().height) };
		box.setPosition(shape.getGlobalBounds().left, shape.getGlobalBounds().top);
		box.setOutlineColor(sf::Color{ 255, 0, 0, 255 });
		box.setOutlineThickness(-2);
		box.setFillColor(sf::Color{ 0, 0, 0, 0 });
		screen.draw(box);
	}
}
sf::FloatRect Entity::getBoundingBox() {
	return shape.getGlobalBounds();
}
void Entity::restrictToBounds(float x, float y, float width, float height) {
	if (getPosition().x > x + width)	getPosition().x = x;
	if (getPosition().x < x)			getPosition().x = x + width;
	if (getPosition().y > y + height)	getPosition().y = y;
	if (getPosition().y < y)			getPosition().y = y + height;
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