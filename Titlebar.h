#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "Gui.h"

class Titlebar
{
private:
	gui::Button* exitButton;
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text title;
	sf::Vector2i grabbedOffset;
	bool isPressed;

public:
	Titlebar(sf::RenderWindow* window, sf::Font* font);
	Titlebar(sf::RenderWindow* window, sf::Font* font, std::string title);
	virtual ~Titlebar();

	void setPressed(bool value);
	const bool getPressed();
	void updateWindowPosition(sf::RenderWindow* window);
	void update(sf::Vector2f mousePosition, sf::RenderWindow* window);
	void render(sf::RenderTarget* target);
};

#endif // !TITLEBAR_H



