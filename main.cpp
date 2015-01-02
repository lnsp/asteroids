#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Meteor.hpp"
#include "ResourceManager.hpp"
#include <iostream>
#include <vector>
#include <cmath>

ResourceManager rm;
const unsigned int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

int main()
{
	using namespace sf;

	// create rendering window with 16x anti aliasing
	RenderWindow window{ VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT }, "Asteroids", Style::Default, ContextSettings{ 16, 16, 16, 2, 0 } };
	window.setVerticalSyncEnabled(true);

	rm.load("player.png");
	rm.load("meteor_big.png");

	// create player object
	Player player{ Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 } };
	player.setRotation(0);

	// meteor vector
	std::vector<Meteor> meteors;

	// create delta timing clock
	Clock clock;
	Time lastTime = clock.getElapsedTime();
	Time lastMeteor = clock.getElapsedTime();

	// key controls
	bool spaceDown = false, leftDown = false, rightDown = false;

	while (window.isOpen()) {
		Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			// close window when pressing on x
			if (windowEvent.type == Event::Closed) {
				window.close();
			}
			// handling shoot, rotate right and left key events
			else if (windowEvent.type == Event::KeyReleased) {
				switch (windowEvent.key.code) {
				case Keyboard::Space:
					spaceDown = false;
					break;
				case Keyboard::A:
					leftDown = false;
					break;
				case Keyboard::D:
					rightDown = false;
					break;
				}
				std::cout << "Key " << windowEvent.key.code << " released" << std::endl;
			}
			else if (windowEvent.type == Event::KeyPressed) {
				switch (windowEvent.key.code) {
				case Keyboard::Space:
					spaceDown = true;
					break;
				case Keyboard::A:
					leftDown = true;
					break;
				case Keyboard::D:
					rightDown = true;
					break;
				}
			}
		}
		window.clear();

		// calculate delta time
		Time elapsedTime = clock.getElapsedTime();
		Time deltaTime = elapsedTime - lastTime;
		lastTime = elapsedTime;
		float delta = deltaTime.asSeconds();
		
		// spawn meteor
		Time distanceTime = elapsedTime - lastMeteor;
		if (distanceTime.asSeconds() > 2) {
			lastMeteor = elapsedTime;

			// randomly calculated position outside the window
			float angle = rand() % 360 * 180 / 3.14f;
			Vector2f meteorPosition{ cos(angle) * WINDOW_WIDTH, sin(angle) * WINDOW_HEIGHT };
			//Vector2f meteorPosition{ 400, 500 };
			// calculate direction
			Vector2f playerPosition = player.getPosition();
			Vector2f direction = playerPosition - meteorPosition;

			std::cout << direction.x << " " << direction.y << std::endl;

			float rotation = atan2(direction.y, direction.x) * 180/3.14f;
			std::cout << rotation << std::endl;

			Meteor m{ meteorPosition };
			m.setSpeed(rand() % 30 + 80);
			m.setRotation(rotation);
			meteors.push_back(m);
		}

		// handle keys
		if (leftDown) {
			player.rotateLeft(delta); // 45 deg per s
		}
		else if (rightDown) {
			player.rotateRight(delta); // 45 deg per s
		}
		if (spaceDown) {
			player.accelerate(1.05f); // accelerate a bit
		}

		// update player
		player.update(delta);
		// draw meteors on screen
		for (auto& asteroid : meteors) {
			asteroid.update(delta);
			asteroid.draw(window);
		}
		// draw player on screen
		player.draw(window);

		
		window.display();
	}
	return 0;
}