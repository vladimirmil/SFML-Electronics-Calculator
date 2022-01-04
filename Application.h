/************************************************************************************
 * @file Application.h
 *
 * @brief Everything gets called from here
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Page.h"
#include "Footer.h"
#include "Titlebar.h"

constexpr auto WINDOW_WIDTH = 1100;
constexpr auto WINDOW_HEIGHT = 640;
constexpr auto FRAMERATE_LIMIT = 60;

class Application
{

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Font font;
	sf::Vector2f mousePositionView;
	std::deque<Page*> pages;
	bool hasFocus;
	void initVariables();
	void initFonts();
	void initWindow();
	void initStates();

	Footer* footer;
	Titlebar* titlebar;
	
public:
	Application();
	virtual ~Application();
	
	const bool isRunning() const;

	void pollEvents();
	void update();
	void render();
	void run();

};

#endif



