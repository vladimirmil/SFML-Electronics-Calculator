#ifndef PAGE_1_H
#define PAGE_1_H

#include "Page.h"
#include "PageMainMenu.h"

class Page1 :
	public Page
{
private:
	sf::RectangleShape background;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::TextBox*> textboxes;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Image*> images;
	std::map<std::string, gui::PopUp*> popups;
	Footer* footer;
	Titlebar* titlebar;
	HandleInput handleinput;

	std::string popup1text, popup2text, popup3text, popup4text;

	short unsigned calculateState;
	enum calculate_state{
		CALC_STATE_0 = 0,
		CALC_STATE_1,
		CALC_STATE_2,
		CALC_STATE_3,
		CALC_STATE_4,
	};

	void initBackground(sf::RenderWindow* window);
	void initPopUpText();
public:

	Page1(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~Page1();

	void calculate(calculate_state calculateState);
	void endState();
	void initGUI();
	void updateGUI();
	void updateInput();
	void updateMouseMov();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !PAGE_ONE_H



