#ifndef PAGE_4_H
#define PAGE_4_H

#include "Page.h"
#include "PageMainMenu.h"

class Page4 :
	public Page
{
private:
	sf::RectangleShape background;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::TextBox*> textboxes;
	std::map<std::string, gui::Label*> labels;
	std::map<std::string, gui::Graph*> graphs;
	std::map<std::string, gui::PopUp*> popups;
	Footer* footer;
	Titlebar* titlebar;
	HandleInput handleinput;
	std::vector<float> inputX, inputY;
	std::string popuptext;

	void initPopUpText();
	void initBackground(sf::RenderWindow* window);
public:

	Page4(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages);
	virtual ~Page4();

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
