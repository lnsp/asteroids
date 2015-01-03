#include <map>
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#pragma once

class ResourceManager {
	std::map<std::string, sf::Texture> textures;
public:
	void load(std::string file);
	sf::Texture* get(std::string file);
};