#include "Projectile.hpp"
#include "ResourceManager.hpp"

void Projectile::init() {
	loadTexture("laser.png");
}
void Projectile::update(float delta) {
	move(delta);
}