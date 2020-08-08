#include <SFML/Graphics.hpp>

#include "Level.h"

#include <list>
#include <time.h>
#include <iostream>
#include <string>

#define DB(x) std::cout << x << std::endl

class Session
{
private:
	//window
	sf::RenderWindow main_window;
	//Mouse
	sf::Vector2i mouse_position;
	bool is_left_mouse_pressed = false;
	//Level
	Level *current_level = new Level();
	
	//debug
	sf::Text fps_label;
	sf::Text mouse_coords_label;
	sf::Font pixel_font;
	
	
	//Settings
	int FPS_border = 1;
	
	//Things to count tick time
	float tick_time;
	clock_t KE_timer;

	//Things to count ticks
	int tick_count;
	
	//Things to count fps
	float one_second_timer;
	float frame_passed_time_count;
	int fps;
	
	//loop for code there
	void loop();
	
	
	//main functions
	void drawFrame();
	void levelTick();
	void mouseHandler();
	void showDebug();
	
	
	//scoring functions
	bool callEveryXTicks(int x);
	
	void fpsCount();
	void tickTimeCount();
	void tickAmountCount();
public:
	Session(int w, int h);
	~Session();
	
	bool isWindowOpen();
	
	void mainLoop();
};
