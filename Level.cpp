#include "Level.h"

Level::Level() 
{
	level_textures = new sf::Texture[1];
	level_sprites = new sf::Sprite[1];

	if (!level_textures[0].loadFromFile("img/wall.png", sf::IntRect(10, 10, 100, 100)))
		DB("Image error");
	else
		DB("Image has been loaded");
	
	level_sprites[0].setTexture(level_textures[0]);
}

void Level::drawLevelFrame(sf::RenderWindow* window)
{
	window->draw(level_sprites[0]);
}

void Level::level_tick(sf::Vector2i* mouse_position, bool is_left_mouse_pressed)
{
	DB("im here");
	if (is_left_mouse_pressed)
		DB("Yes");
	else
		DB("No");

	if (is_left_mouse_pressed)
		level_sprites[0].setPosition((float)mouse_position->x, (float)mouse_position->y);
}

Level::~Level() 
{
	delete[] level_textures;
	delete[] level_sprites;
}
