#include <SFML/Graphics.hpp>

#include "Level.h"
#include "ErrorHandler.h"

#include <list>
#include <chrono>
#include <iostream>
#include <string>
#include <math.h> 

#ifdef __linux__ 
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

class Session
{
private:
	//window
	sf::RenderWindow main_window;
	//Mouse
	sf::Vector2i mouse_position;
	bool is_left_mouse_pressed = false;
	//Level
	Level *current_level;
	
	//debug
	sf::Text fps_label;
	sf::Text mouse_coords_label;
	sf::Text timer_label;
	sf::Text tick_time_label;
	
	sf::Font pixel_font;
	
	ErrorHandler *eh;
	
	//Settings
	int FPS_border = 60;
	double base_ticks_time = 0.01f; // 1/100
	
	//Things to count time
	double tick_time;
	int seconds;

	//Things to count ticks
	int tick_count;
	
	//Things to count fps
	double one_second_timer;
	double frame_passed_time_count;
	int fps;
	
	//loop for code there
	void loop();
	
	
	//main functions
	void drawFrame();
	void levelTick();
	void eventHandler();
	void mouseHandler();
	void showDebug();
	void sleep();
	
	
	//scoring functions
	bool callEveryXTicks(int x);
	
	void fpsCount();
	void tickTimeCount();
	void tickAmountCount();
	
	//init funcs
	void fontsInit();
	void countersInit();
	void windowInit(int w, int h);
public:
	Session(int w, int h);
	~Session();
	
	bool isWindowOpen();
	
	void mainLoop();
};
