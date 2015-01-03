#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Meteor.hpp"
#include "ResourceManager.hpp"

ResourceManager resourceManager;
const unsigned int		WINDOW_WIDTH		= 1280,
						WINDOW_HEIGHT		= 720;
const sf::Keyboard::Key ROTATE_LEFT_KEY		= sf::Keyboard::A,
						ROTATE_RIGHT_KEY	= sf::Keyboard::D,
						ACCELERATE_KEY		= sf::Keyboard::Space,
						SHOOT_KEY			= sf::Keyboard::P;

int main()
{
	using namespace sf;

	// create rendering window with 16x anti aliasing
	RenderWindow window{ VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT }, "Asteroids", Style::Default, ContextSettings{ 16, 16, 16, 2, 0 } };
	window.setVerticalSyncEnabled(true);

	// load resources
	resourceManager.load("player.png");
	resourceManager.load("meteor_big.png");
	resourceManager.load("laser.png");

	// create player object
	Player player{ Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 } };
	player.setRotation(0);

	// meteor vector
	std::vector<Meteor> meteors;
	// projectile vector
	std::vector<Projectile> projectiles;

	// create delta timing clock
	Clock gameClock;
	Time lastTime			= gameClock.getElapsedTime();

	// key controls
	bool accelerateKeyDown = false, rotateLeftKeyDown = false, rotateRightKeyDown = false, shootKeyDown = false;

	while (window.isOpen()) {
		Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			// close window when pressing on x
			if (windowEvent.type == Event::Closed) {
				window.close();
			}
			// handling shoot, rotate right and left key events
			else if (windowEvent.type == Event::KeyReleased || windowEvent.type == Event::KeyPressed) {
				bool state = windowEvent.type == Event::KeyPressed;
				switch (windowEvent.key.code) {
				case ACCELERATE_KEY:
					accelerateKeyDown	= state;
					break;
				case ROTATE_LEFT_KEY:
					rotateLeftKeyDown	= state;
					break;
				case ROTATE_RIGHT_KEY:
					rotateRightKeyDown	= state;
					break;
				case SHOOT_KEY:
					shootKeyDown		= state;
				}
			}
		}
		window.clear();

		// calculate delta time
		Time elapsedTime	= gameClock.getElapsedTime();
		Time deltaTime		= elapsedTime - lastTime;
		lastTime			= elapsedTime;
		float delta			= deltaTime.asSeconds();

		// handle keys
		if (rotateLeftKeyDown) {
			player.rotateLeft(delta);
		}
		else if (rotateRightKeyDown) {
			player.rotateRight(delta);
		}
		if (accelerateKeyDown) {
			player.accelerate(1.05f); // accelerate a bit
		}
		if (shootKeyDown) {
			player.shoot(projectiles, elapsedTime);
		}

		// update player
		player.update(delta);

		// spawn meteors
		Meteor::spawn(meteors, player.getPosition(), elapsedTime, 800);

		// keep player inside window
		player.restrictToBounds(0.0f, 0.0f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT));


		// draw meteors on screen
		for (auto& asteroid : meteors) {
			asteroid.update(delta);
			asteroid.draw(window);
		}

		// draw player on screen
		player.draw(window);
		// draw projectiles on screen
		for (auto& shot : projectiles) {
			shot.update(delta);
			shot.draw(window);
		}
		
		// switch buffers for double-buffering
		window.display();
	}
	return 0;
}