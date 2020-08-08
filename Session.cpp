#include "Session.h"

Session::Session(int w, int h) 
{
	main_window.create(sf::VideoMode(w, h), "SFML works!");
	
	KE_timer = clock();	
	
	tick_count = 0;
	frame_passed_time_count = 0;
	fps = 0;
	one_second_timer = 0;
	
	if (!pixel_font.loadFromFile("fonts/pixel_font.ttf"))
	{
		DB("font error");
	}
	
	mouse_coords_label.setFont(pixel_font);
	fps_label.setFont(pixel_font);
	
	
	mouse_coords_label.setPosition(sf::Vector2f(0, 10));
	mouse_coords_label.setCharacterSize(10);
	fps_label.setCharacterSize(10);
}

//Outer loop, which is called from outside
void Session::mainLoop()
{
	while (main_window.isOpen())
	{
		sf::Event event;
		while (main_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			main_window.close();
		}
		
		//all is happening here
		loop();
	}
}

//inner loop, which drives all gamestuff
void Session::loop()
{
	tickTimeCount();
	tickAmountCount();
	fpsCount();
	
	mouseHandler();
	
	if (frame_passed_time_count > 1.0f / FPS_border)
	{
		drawFrame();
	}
	
	levelTick();
}

void Session::drawFrame()
{		
	//FPS count
	fps++;
	frame_passed_time_count = 0;
	
	//Clearing da screen
	main_window.clear(sf::Color::Black);
	
	//Draw
	current_level->drawLevelFrame(&main_window);
	showDebug();
	
	//display frame
	main_window.display();
}

void Session::levelTick()
{
	current_level->level_tick(&mouse_position, is_left_mouse_pressed);
}

void Session::mouseHandler()
{
	mouse_position = sf::Mouse::getPosition(main_window);
	mouse_coords_label.setString("MouseX: " + std::to_string(mouse_position.x) + " | MouseY: " + std::to_string(mouse_position.y));
	
	is_left_mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Session::showDebug()
{
	main_window.draw(mouse_coords_label);
	main_window.draw(fps_label);
}

bool Session::callEveryXTicks(int x)
{
	
}

void Session::fpsCount()
{
	frame_passed_time_count += tick_time;
	one_second_timer += tick_time;
	
	if (one_second_timer > 1.0f) 
	{
		fps_label.setString("FPS: " + std::to_string(fps));
		DB(fps);
		DB(mouse_position.x);
		DB(mouse_position.y);
		DB("*****************");
		one_second_timer = 0;
		fps = 0;
	}
}

void Session::tickTimeCount()
{	
	tick_time = ((float)(clock() - KE_timer))/CLOCKS_PER_SEC;
	
	KE_timer = clock();
}

void Session::tickAmountCount()
{
	tick_count++;	
	
	tick_count = (tick_count <= 1000) * tick_count; 
}

bool Session::isWindowOpen()
{
	return main_window.isOpen();
}

Session::~Session()
{
	delete current_level;
}
