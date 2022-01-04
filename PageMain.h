/************************************************************************************
 * @file PageMain.h
 *
 * @brief Contents of page main
 *
 * @author Vladimir Milivojevic
 *
 ************************************************************************************/

#ifndef PAGE_MAIN_H
#define PAGE_MAIN_H

#include "Page.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"

class PageMain :
	public Page
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Label*> labels;
	sf::RectangleShape background;
public:

	PageMain(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~PageMain();

	void endState();
	void initGUI();
	void updateGUI();
	void updateInput();
	void update();
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

