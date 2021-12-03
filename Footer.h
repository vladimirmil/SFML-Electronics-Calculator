#ifndef FOOTER_H
#define FOTTER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

const std::string sVersion = "v1.0";

class Footer
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text author;
	sf::Text version;
public:
	Footer(sf::RenderWindow* window, sf::Font* font);
	virtual ~Footer();

	void render(sf::RenderTarget* target);
};

#endif // !FOOTER_H



