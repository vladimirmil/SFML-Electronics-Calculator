#ifndef PAGE_THREE_H
#define PAGE_THREE_H

#include "State.h"
#include "MainMenu.h"

class PageThree :
	public State
{
private:
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::Graph*> graphs;
	Footer* footer;
	Titlebar* titlebar;
	sf::RectangleShape background;
	std::vector<float> input;
	std::vector<float> inputX;
	std::vector<float> inputY;

	void initBackground(sf::RenderWindow* window);
public:

	PageThree(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~PageThree();

	void updateInput();
	void updateMouseMov();

	void endState();
	void initGUI();
	void updateGUI();
	void update(/*const float& dt*/);
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif
