#include "ResourceManager.hpp"

void ResourceManager::load(std::string file) {
	sf::Texture image;
	image.loadFromFile(file);
	textures.insert(std::pair<std::string, sf::Texture>(file, image));
	std::cout << "Loaded file " << file << std::endl;
}
sf::Texture* ResourceManager::get(std::string file) {
	return &textures.at(file);
}