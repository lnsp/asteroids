#include "SFML\Graphics.hpp"
#pragma once

class Entity {
	float rotation = 0, speed = 0;
	sf::Vector2f position{ 0, 0 };
protected:
	sf::Sprite shape;
	sf::Texture* texture;
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
	void update(float delta);
};