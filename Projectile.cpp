#include "Projectile.hpp"
#include "ResourceManager.hpp"

const float Projectile::MAX_LIFETIME = 800.0f;
void Projectile::init() {
	loadTexture("laser.png");
}
bool Projectile::update(float delta, std::vector<Meteor>& meteors) {
	float distance = move(delta);

	lifetime += distance;
	if (lifetime > MAX_LIFETIME)
		return true;
	
	for (auto it = meteors.begin(); it != meteors.end(); ++it) {
		if (it->getBoundingBox().intersects(getBoundingBox())) {
			meteors.erase(it);
			return true;
		}
	}
	return false;
}
void Projectile::draw(sf::RenderWindow& screen) {
	sf::Uint8 def = 255 - (lifetime / MAX_LIFETIME) * 255;
	shape.setColor(sf::Color{ def, def, def, def });
	shape.setRotation(getRotation());
	shape.setPosition(getPosition());
	screen.draw(shape);
}