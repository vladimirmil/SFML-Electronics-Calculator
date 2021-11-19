#ifndef TEST_MENU_H
#define TEST_MENU_H

#include "State.h"
#include "MainMenu.h"

class TestMenu :
	public State
{
private:
	std::map<std::string, Button*> buttons;
public:

	TestMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~TestMenu();

	void endState();
	void initGUI();
	void updateGUI();
	void update(/*const float& dt*/);
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif
