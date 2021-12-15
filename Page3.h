#ifndef PAGE_3_H
#define PAGE_3_H

#include "Page.h"
#include "PageMainMenu.h"

class Page3 :
	public Page
{
private:
	sf::RectangleShape background;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	Footer* footer;
	Titlebar* titlebar;

	void initBackground(sf::RenderWindow* window);
public:

	Page3(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~Page3();

	void updateInput();
	void updateMouseMov();

	void endState();
	void initGUI();
	void updateGUI();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif
