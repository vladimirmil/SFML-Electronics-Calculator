#ifndef PAGE_ONE_H
#define PAGE_ONE_H

#include "State.h"
#include "MainMenu.h"
#include <string>

class PageOne :
	public State
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::TextBox*> textboxes;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Image*> images;
	Footer* footer;
	Titlebar* titlebar;
	HandleInput handleinput;
	sf::RectangleShape background;

	short unsigned calculateState;
	enum calculate_state{
		CALC_STATE_0 = 0,
		CALC_STATE_1,
		CALC_STATE_2,
		CALC_STATE_3,
		CALC_STATE_4,
	};

	void initBackground(sf::RenderWindow* window);
public:

	PageOne(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~PageOne();

	void calculate();
	void endState();
	void initGUI();
	void updateGUI();
	void updateInput();
	void updateMouseMov();
	void update(/*const float& dt*/);
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !PAGE_ONE_H



