#ifndef APPLICATION_H
#define APPLICATION_H

#include "State.h"

constexpr auto WINDOW_WIDTH = 1100;
constexpr auto WINDOW_HEIGHT = 640;
constexpr auto FRAMERATE_LIMIT = 60;

class Application
{

private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//sf::Clock dtClock;
	//float dt;
	std::deque<State*> states;

	void initVariables();
	void initWindow();
	void initStates();
	
public:
	Application();
	virtual ~Application();
	
	const bool isRunning() const;

	void pollEvents();
	//void updateDt();
	void update(/*const float& dt*/);
	void render();
	void run();

};

#endif



