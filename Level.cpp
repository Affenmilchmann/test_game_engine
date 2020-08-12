#include "Level.h"

Level::Level() {}

Level::Level(ErrorHandler* eh, int seconds) 
{
	this->eh = eh;

	level_textures = new sf::Texture[1];
	level_sprites = new sf::Sprite[1];

	if (!level_textures[0].loadFromFile("img/wall.png"))
	{
		DB("Image error");
		
		eh->getError(1, seconds); //1 is a code of texture error.
	}
	else
	{
		DB("Image has been loaded");
	}
	
	level_sprites[0].setTexture(level_textures[0]);
	level_sprites[0].setTextureRect({ 0, 0, 96, 96 });
}

void Level::drawLevelFrame(sf::RenderWindow* window)
{
	window->draw(level_sprites[0]);
}

void Level::level_tick(sf::Vector2i* mouse_position, bool is_left_mouse_pressed)
{
	//level_sprites[0].setPosition(mouse_position->x, mouse_position->y);
}

void Level::loadLevelFromFile(std::string file_name)
{
	//std::ifstream level_file;
}

Level::~Level() 
{
	delete[] level_textures;
	delete[] level_sprites;
}
