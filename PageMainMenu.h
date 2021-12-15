#ifndef PAGE_MAIN_MENU_H
#define PAGE_MAIN_MENU_H

#include "Page.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"

class PageMainMenu :
	public Page
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	Titlebar* titlebar;
	Footer* footer;
	sf::RectangleShape background;
public:

	PageMainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~PageMainMenu();

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

