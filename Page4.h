/************************************************************************************
 * @file Page4.h
 *
 * @brief Contents of page 4
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/
#ifndef PAGE_4_H
#define PAGE_4_H

#include "Page.h"
#include "PageMain.h"

class Page4 :
	public Page
{
private:
	sf::RectangleShape background;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;

	void initBackground(sf::RenderWindow* window);
public:

	Page4(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~Page4();

	void updateInput();

	void endState();
	void initGUI();
	void updateGUI();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif
