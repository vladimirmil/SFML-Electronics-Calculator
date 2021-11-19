#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.h"
#include "TestMenu.h"

static const sf::Color BLUE_IDLE = sf::Color(43, 107, 255, 255);
static const sf::Color BLUE_HOVER = sf::Color(61, 120, 255, 255);
static const sf::Color BLUE_PRESSED = sf::Color(31, 99, 255, 255);

static const sf::Color YELLOW_IDLE = sf::Color(255, 179, 0, 255);
static const sf::Color YELLOW_HOVER = sf::Color(250, 175, 0, 255);
static const sf::Color YELLOW_PRESSED = sf::Color(246, 164, 0, 255);

class MainMenu :
	public State
{
private:
	std::map<std::string, Button*> buttons;
	std::map<std::string, TextBox*> textboxes;
	std::map<std::string, Label*> labels;
public:

	MainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~MainMenu();

	void endState();
	void initGUI();
	void updateGUI();
	void update(/*const float& dt*/);
	void renderGUI(sf::RenderTarget * target);
	void render(sf::RenderTarget* target = nullptr);
};
#endif

