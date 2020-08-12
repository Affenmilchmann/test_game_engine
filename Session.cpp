#include "Session.h"

//Constructor and initialization
Session::Session(int w, int h) 
{
	windowInit(w, h);
	countersInit();
	fontsInit();
	eh = new ErrorHandler(pixel_font);
	current_level = new Level(eh, seconds);
}

////////////////////////////////////////////
//Outer loop, which is called from outside//
////////////////////////////////////////////
void Session::mainLoop()
{
	while (main_window.isOpen())
	{	
		eventHandler();
	
		auto KE_timer_start = std::chrono::steady_clock::now();
		
		//all is happening here
		loop();
		
		auto KE_timer_end = std::chrono::steady_clock::now();
		
		std::chrono::duration<double> elapsed_seconds = KE_timer_end - KE_timer_start;
		tick_time = elapsed_seconds.count();
		
	}
}

//////////////////////////////////////////
//inner loop, which drives all gamestuff//
//////////////////////////////////////////
void Session::loop()
{	
	//sleep so every tick is limited by base_ticks_time
	sleep();
	//counting ticks amount
	tickAmountCount();
	//counting FPS
	fpsCount();
	
	//handling the mouse, i guess
	mouseHandler();
	
	//drawing frame if fps border allows
	if (frame_passed_time_count >= 1.0 / FPS_border)
		drawFrame();
	
	//level physics (raw)
	levelTick();
	
	//eh is a HandlerUpdate object. Here it checks if error message must be erased (because of time)
	eh->errorHandlerUpdate(seconds);
}

///////////////////
//Major functions//
///////////////////
void Session::drawFrame()
{		
	//FPS count
	fps++;
	frame_passed_time_count = 0;
	
	//Clearing da screen
	main_window.clear(sf::Color::Black);
	
	//Draw level objects
	current_level->drawLevelFrame(&main_window);
	
	//Draw Debug and Errors
	showDebug();
	eh->drawErrors(&main_window); //here eh draws error messages
	
	//display frame
	main_window.display();
}

void Session::levelTick()
{
	current_level->level_tick(&mouse_position, is_left_mouse_pressed);
}

void Session::eventHandler()
{
	sf::Event event;
	while (main_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			main_window.close();
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
			main_window.setView(sf::View(visibleArea));
		}
	}
}

void Session::mouseHandler()
{
	mouse_position = sf::Mouse::getPosition(main_window);
	
	is_left_mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Session::showDebug()
{
	//Setting values
	if (one_second_timer > 1.0f) 
		fps_label.setString("FPS: " + std::to_string(fps));
		
	mouse_coords_label.setString("MouseX: " + std::to_string(mouse_position.x) +
				   " | MouseY: " + std::to_string(mouse_position.y));
		
	timer_label.setString("Time(s): " + std::to_string(one_second_timer + seconds));
	
	tick_time_label.setString("Tick time(s): " + std::to_string(tick_time));
	
	//draw Debug info (it is written here because i dont want it to be independent from fps
	main_window.draw(mouse_coords_label);
	main_window.draw(fps_label);
	main_window.draw(timer_label);
	main_window.draw(tick_time_label);
}

void Session::sleep() 
{
	//Sleep if tick time is lower than base_ticks_time
	int time = floor((base_ticks_time - tick_time) / 2 * (base_ticks_time - tick_time > 0) * 1000);

#ifdef __linux__ 
	usleep(time * 1000);
#endif
#ifdef WINDOWS
	Sleep(time);
#endif
	/*DB("Tick time:(ms)");
	DB(tick_time * 1000);
	DB("Base tick time:(ms)");
	DB(base_ticks_time * 1000);
	DB("Sleeping for(ms):");
	DB(time);
	DB("**********");*/
}

///////////////////
//Minor functions//
///////////////////
bool Session::callEveryXTicks(int x)
{
	return true;
}

void Session::fpsCount()
{
	frame_passed_time_count += tick_time;
	one_second_timer += tick_time;
	
	if (one_second_timer > 1.0f) 
	{
		fps_label.setString("FPS: " + std::to_string(fps));
		one_second_timer = 0;
		fps = 0;
		seconds++;
	}
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

//////////////////
//Init functions//
//////////////////
void Session::fontsInit()
{
	if (!pixel_font.loadFromFile("fonts/pixel_font.ttf"))
	{
		DB("font error");
	}
	
	mouse_coords_label.setFont(pixel_font);
	fps_label.setFont(pixel_font);
	timer_label.setFont(pixel_font);
	tick_time_label.setFont(pixel_font);
	
	fps_label.setCharacterSize(20);
	
	mouse_coords_label.setPosition(sf::Vector2f(0, 20));
	mouse_coords_label.setCharacterSize(20);
	
	timer_label.setPosition(sf::Vector2f(0, 40));
	timer_label.setCharacterSize(20);
	
	tick_time_label.setPosition(sf::Vector2f(0, 60));
	tick_time_label.setCharacterSize(20);
}

void Session::countersInit()
{	
	tick_count = 0;
	frame_passed_time_count = 0;
	fps = 0;
	one_second_timer = 0;
	seconds = 0;
}

void Session::windowInit(int w, int h)
{
	main_window.create(sf::VideoMode(w, h), "SFML works!");
}

Session::~Session()
{
	delete current_level;
	delete eh;
}
