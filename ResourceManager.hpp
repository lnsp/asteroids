#include <map>
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#pragma once

class ResourceManager {
	std::map<std::string, sf::Texture> textures;
public:
	void load(std::string file) {
		sf::Texture image;
		image.loadFromFile(file);
		textures.insert(std::pair<std::string, sf::Texture>(file, image));
		std::cout << "Loaded file " << file << std::endl;
	}
	sf::Texture* get(std::string file) {
		std::cout << "Requested file " << file << std::endl;
		return &textures.at(file);
	}
};