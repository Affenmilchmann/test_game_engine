#include <SFML/Graphics.hpp>

#include "Session.h"

#include <iostream>

int main()
{
    	//Session main_ses(1280,720);
    	Session main_ses(1000,600);
    
    	main_ses.mainLoop();
    	
    	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;*/
}
