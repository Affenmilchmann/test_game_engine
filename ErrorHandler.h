#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <list>
#include <iostream>

#define DB(x) std::cout << x << std::endl

class ErrorHandler 
{
public:
	ErrorHandler(sf::Font text_font);
	~ErrorHandler();

	void getError(int code, int sec_time);
	void drawErrors(sf::RenderWindow* main_window);
	void errorHandlerUpdate(int sec_time);
private:
	std::string* messages;
	std::list<sf::Text> errors;
	std::list<int> timers;
	
	sf::Font text_font;
	
	int life_time_seconds = 3;
	
	int char_size = 20;
};
