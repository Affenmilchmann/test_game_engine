#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(sf::Font text_font)
{
	this->text_font = text_font;
	
	messages = new std::string[10];
	messages[0] = "while loading level.";
	messages[1] = "while loading texture.";
}

void ErrorHandler::getError(int code, int sec_time)
{
	//Making error message time stamp
	timers.push_front(sec_time);
	//Making error message
	errors.push_front(sf::Text());
	
	errors.front().setFont(text_font);
	errors.front().setCharacterSize(char_size);
	errors.front().setString("Error was orrured " + messages[code]);
	errors.front().setPosition(sf::Vector2f(300, char_size * (errors.size() - 1)));
}

void ErrorHandler::drawErrors(sf::RenderWindow* main_window)
{
	if (errors.empty()) return;
	
	for (sf::Text t : errors)
		main_window->draw(t);
}

void ErrorHandler::errorHandlerUpdate(int sec_time)
{
	if (!timers.empty() && sec_time - timers.back() > life_time_seconds)
	{
		timers.pop_back();
		errors.pop_back();
		
		int i = 0;
		for (sf::Text t : errors)
		{
			t.setPosition(300.f, (float)(char_size * i));
			i++;
		}
	}
}

ErrorHandler::~ErrorHandler()
{
	delete[] messages;
	errors.clear();
	timers.clear();
}
