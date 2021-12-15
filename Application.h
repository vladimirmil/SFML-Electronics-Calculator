#ifndef APPLICATION_H
#define APPLICATION_H

#include "Page.h"

constexpr auto WINDOW_WIDTH = 1100;
constexpr auto WINDOW_HEIGHT = 640;
constexpr auto FRAMERATE_LIMIT = 60;

class Application
{

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::deque<Page*> pages;
	bool hasFocus;
	void initVariables();
	void initWindow();
	void initStates();
	
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



