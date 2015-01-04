#include "SFML\Graphics.hpp"
#pragma once

class Entity {
	float rotation = 0, speed = 0;
	sf::Vector2f position{ 0, 0 };
	sf::Texture* texture;
protected:
	void loadTexture(std::string file);
	sf::Sprite shape;
	float move(float delta);
public:
	Entity(sf::Vector2f& position);
	Entity() {};
	sf::Vector2f& getPosition();
	float getRotation();
	float getSpeed();
	void setSpeed(float speed);
	void rotate(float amount);
	void setPosition(sf::Vector2f& position);
	void setRotation(float rotation);
	void draw(sf::RenderWindow& screen);
	void draw(sf::RenderWindow& screen, bool drawBoundingBox);
	void restrictToBounds(float x, float y, float width, float height);
	void update(float delta);
	sf::FloatRect Entity::getBoundingBox();
};