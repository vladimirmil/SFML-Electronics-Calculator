#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.h"
#include "PageOne.h"
#include "PageTwo.h"
#include "PageThree.h"
#include "PageFour.h"

class MainMenu :
	public State
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	Titlebar* titlebar;
	Footer* footer;
	sf::RectangleShape background;
public:

	MainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~MainMenu();

	void endState();
	void initGUI();
	void updateGUI();
	void updateInput();
	void updateMouseMov();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

