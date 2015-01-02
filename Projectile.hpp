#include "SFML\Graphics.hpp"
#pragma once
/**

REWORK THIS CLASS TO Projectile : Entity

**/


enum class ProjectileType {
	FRIENDLY,
	HOSTILE
};

class Projectile {
	sf::Vector2f position{ 0, 0 };
	sf::Vector2f direction{ 0, 0 };
	float speed = 1;
	ProjectileType type{ ProjectileType::FRIENDLY };
public:
	Projectile(sf::Vector2f& position, sf::Vector2f& direction, float speed, ProjectileType type);
	Projectile() {};
	sf::Vector2f& getPosition();
	sf::Vector2f& getDirection();
	float getSpeed();
	ProjectileType getType();
	void setPosition(sf::Vector2f& position);
	void setDirection(sf::Vector2f& direction);
	void setSpeed(float speed);
	void update(float delta);
	void draw(sf::RenderWindow& screen);
};