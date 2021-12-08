#ifndef PAGE_FOUR_H
#define PAGE_FOUR_H

#include "State.h"
#include "MainMenu.h"

class PageFour :
	public State
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

	PageFour(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~PageFour();

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
