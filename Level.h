#include <SFML/Graphics.hpp>

#include <list>
#include <string>
#include <iostream>
#include <fstream>

#include "ErrorHandler.h"

#define DB(x) std::cout << x << std::endl

class Level
{
private:
	sf::Texture* level_textures;
	sf::Sprite* level_sprites;
	
	ErrorHandler* eh;
	
public:
	Level();
	Level(ErrorHandler* eh, int seconds);
	~Level();
	
	void loadLevelFromFile(std::string file_name);
	
	void drawLevelFrame(sf::RenderWindow* window);
	void level_tick(sf::Vector2i* mouse_position, bool is_left_mouse_pressed);
};
