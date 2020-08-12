#include "ErrorHandler.h"

//Constructor
ErrorHandler::ErrorHandler(sf::Font text_font)
{
	//takes outer font to init its fonts
	this->text_font = text_font;
	
	//a bit weird but here error texts are written
	messages = new std::string[10];
	messages[0] = "while loading level.";
	messages[1] = "while loading texture.";
}

//This func is called in main programm to make new error message (i think i must rename it lol)
void ErrorHandler::getError(int code, int sec_time)
{
	//Making error message time stamp
	timers.push_front(sec_time);
	
	//Making error message
	errors.push_front(sf::Text());
	//Setting errors text settings
	errors.front().setFont(text_font);
	errors.front().setCharacterSize(char_size);
	errors.front().setString("Error was orrured " + messages[code]);
	errors.front().setPosition(sf::Vector2f(300, char_size * (errors.size() - 1)));
}

//This func is called in main draw loop (Session->drawFrame()) to draw error messanges
void ErrorHandler::drawErrors(sf::RenderWindow* main_window)
{
	if (errors.empty()) return;
	
	for (sf::Text t : errors)
		main_window->draw(t);
}

//This func is called in loop (Session->loop()) and it controls time messages are shown (and deletes is time had came to end)
void ErrorHandler::errorHandlerUpdate(int sec_time)
{
	if (!timers.empty() && sec_time - timers.back() > life_time_seconds)
	{
		//deletting expiered one
		timers.pop_back();
		errors.pop_back();
		
		//moving others messages higher (does not work i dont know why)
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
