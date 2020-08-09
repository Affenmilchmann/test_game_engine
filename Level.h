#include <SFML/Graphics.hpp>

#include <list>
#include <string>
#include <iostream>

#define DB(x) std::cout << x << std::endl

class Level
{
private:
	sf::Texture* level_textures;
	sf::Sprite* level_sprites;
	
public:
	Level();
	~Level();
	
	void loadLevelFromFile(std::string file_name);
	
	void drawLevelFrame(sf::RenderWindow* window);
	void level_tick(sf::Vector2i* mouse_position, bool is_left_mouse_pressed);
};
