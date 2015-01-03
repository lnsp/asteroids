#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Meteor.hpp"
#include "ResourceManager.hpp"

ResourceManager resourceManager;
const unsigned int		WINDOW_WIDTH = 800,
						WINDOW_HEIGHT = 600;
const sf::Keyboard::Key ROTATE_LEFT_KEY = sf::Keyboard::A,
						ROTATE_RIGHT_KEY = sf::Keyboard::D,
						ACCELERATE_KEY = sf::Keyboard::Space;

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

	// create delta timing clock
	Clock gameClock;
	Time lastTime	= gameClock.getElapsedTime();
	Time lastMeteor = gameClock.getElapsedTime();

	// key controls
	bool accelerateKeyDown = false, rotateLeftKeyDown = false, rotateRightKeyDown = false;

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
					accelerateKeyDown = state;
					break;
				case ROTATE_LEFT_KEY:
					rotateLeftKeyDown = state;
					break;
				case ROTATE_RIGHT_KEY:
					rotateRightKeyDown = state;
					break;
				}
			}
		}
		window.clear();

		// calculate delta time
		Time elapsedTime = gameClock.getElapsedTime();
		Time deltaTime = elapsedTime - lastTime;
		lastTime = elapsedTime;
		float delta = deltaTime.asSeconds();
		
		// spawn meteor
		Time distanceTime = elapsedTime - lastMeteor;
		if (distanceTime.asSeconds() > 2) {
			lastMeteor = elapsedTime;

			// generate random position outside the window
			float angle = rand() % 360 * 180 / 3.14f;
			Vector2f meteorPosition{ cos(angle) * WINDOW_WIDTH, sin(angle) * WINDOW_HEIGHT };

			// calculate direction to throw it to the player
			Vector2f playerPosition = player.getPosition();
			Vector2f direction = playerPosition - meteorPosition;

			// vector to angle
			float rotation = atan2(direction.y, direction.x) * 180/3.14f;
			std::cout << rotation << std::endl;

			// create object and append it to the vector
			Meteor m{ meteorPosition };
			m.setSpeed(rand() % 30 + 80);
			m.setRotation(rotation);
			meteors.push_back(m);

			//TODO: Remove debug msg
			std::cout << "meteor spawned at " << meteorPosition.x << "; " << meteorPosition.y << std::endl;
		}

		// handle keys
		if (rotateLeftKeyDown) {
			player.rotateLeft(delta); // 45 deg per s
		}
		else if (rotateRightKeyDown) {
			player.rotateRight(delta); // 45 deg per s
		}
		if (accelerateKeyDown) {
			player.accelerate(1.05f); // accelerate a bit
		}

		// update player
		player.update(delta);

		// keep player inside window
		player.restrictToBounds(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		// draw meteors on screen
		for (auto& asteroid : meteors) {
			asteroid.update(delta);
			asteroid.draw(window);
		}
		// draw player on screen
		player.draw(window);
		
		// switch buffers for double-buffering
		window.display();
	}
	return 0;
}