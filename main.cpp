#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Meteor.hpp"
#include "ResourceManager.hpp"

ResourceManager resourceManager;
const unsigned int		WINDOW_WIDTH = 1280,
WINDOW_HEIGHT = 720;
const sf::Keyboard::Key ROTATE_LEFT_KEY = sf::Keyboard::A,
ROTATE_RIGHT_KEY = sf::Keyboard::D,
ACCELERATE_KEY = sf::Keyboard::Space,
SHOOT_KEY = sf::Keyboard::P;

int main()
{
	using namespace sf;

	// create rendering window with 16x anti aliasing
	RenderWindow window{ VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT }, "Asteroids", Style::Default, ContextSettings{ 16, 16, 16, 2, 0 } };
	window.setVerticalSyncEnabled(true);

	int playerScore = 0;

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
	Time lastTime = gameClock.getElapsedTime();

	Font gameFont;
	gameFont.loadFromFile("Starjedi.ttf");

	Text gameOverText;
	gameOverText.setFont(gameFont);
	gameOverText.setCharacterSize(42);
	gameOverText.setString("Game over! press p to restart");
	gameOverText.setPosition(220, 500);

	Text hpText;
	hpText.setFont(gameFont);
	hpText.setPosition(20, 20);
	hpText.setCharacterSize(24);
	hpText.setString(std::to_string(player.getHP()) + " / " + std::to_string(player.getMaxHP()));

	Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setPosition(1000, 20);
	scoreText.setCharacterSize(24);
	scoreText.setString("Score: " + std::to_string(playerScore));
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
					accelerateKeyDown = state;
					break;
				case ROTATE_LEFT_KEY:
					rotateLeftKeyDown = state;
					break;
				case ROTATE_RIGHT_KEY:
					rotateRightKeyDown = state;
					break;
				case SHOOT_KEY:
					shootKeyDown = state;
				}
			}
		}
		window.clear();

		// calculate delta time
		Time elapsedTime = gameClock.getElapsedTime();
		Time deltaTime = elapsedTime - lastTime;
		lastTime = elapsedTime;
		float delta = deltaTime.asSeconds();

		if (!player.isDead()) {
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
			player.update(delta, meteors);

			// spawn meteors
			Meteor::spawn(meteors, player.getPosition(), elapsedTime, 800);

			// keep player inside window
			player.restrictToBounds(0.0f, 0.0f, float(WINDOW_WIDTH), float(WINDOW_HEIGHT));
			// update projectiles
			int meteorLength = meteors.size();
			for (auto projIt = projectiles.begin(); projIt != projectiles.end(); ++projIt) {
				if (projIt->update(delta, meteors)) {
					projectiles.erase(projIt);
					if (meteors.size() != meteorLength)
						playerScore += 10;
					break;
				}
				else {
					projIt->restrictToBounds(-100.f, -100.f, float(WINDOW_WIDTH + 100), float(WINDOW_HEIGHT + 100));
				}
			}

			// draw meteors on screen
			for (auto& asteroid : meteors) {
				asteroid.update(delta);
				asteroid.restrictToBounds(-200.0f, -200.0f, float(WINDOW_WIDTH + 200), float(WINDOW_HEIGHT + 200));
			}
			hpText.setString(std::to_string(player.getHP()) + " / " + std::to_string(player.getMaxHP()));
			scoreText.setString("Score: " + std::to_string(playerScore));
		}
		else {
			window.draw(gameOverText);

			if (shootKeyDown) {
				meteors.clear();
				projectiles.clear();
				Meteor::spawning_rate = 1.0f;
				player.setPosition(Vector2f{ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
				playerScore = 0;
				player.resetHP();
			}
		}

		// draw player on screen
		player.draw(window);

		for (auto& asteroid : meteors) {
			asteroid.draw(window);
		}
		// draw projectiles on screen
		for (auto& shot : projectiles) {
			shot.draw(window);
		}
		window.draw(hpText);
		window.draw(scoreText);


		// switch buffers for double-buffering
		window.display();
	}
	return 0;
}