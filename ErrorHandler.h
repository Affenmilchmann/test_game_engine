#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <list>
#include <iostream>

#define DB(x) std::cout << x << std::endl

class ErrorHandler 
{
public:
	//Constructor
	ErrorHandler(sf::Font text_font);
	//Destructor
	~ErrorHandler();

	//Func to form new error message
	void getError(int code, int sec_time);
	//func to display errors
	void drawErrors(sf::RenderWindow* main_window);
	//func to delete expired ones
	void errorHandlerUpdate(int sec_time);
	
private:
	//string array for storing error texts
	std::string* messages;
	//errors are stored in sf::Text array
	std::list<sf::Text> errors;
	//array with timers of each error message
	std::list<int> timers;
	
	//var to take Font from the main programm and set it sf::Texts
	sf::Font text_font;
	
	//lifetime of each message in seconds
	int life_time_seconds = 3;
	
	//size of messages texts
	int char_size = 20;
};
