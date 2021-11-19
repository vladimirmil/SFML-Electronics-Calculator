#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stack>

#include "Button.h"
#include "TextBox.h"
#include "Label.h"

class State
{
protected:
	std::deque<State*>* states;
	sf::RenderWindow* window;
	sf::Event* ev;
	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Font font;
	bool quit;

public:
	State(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void setQuit(bool quit);

	void initFonts();

	virtual void checkQuit();
	virtual void updateMousePositions();

	virtual void endState() = 0;
	virtual void update(/*const float& dt*/) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif



