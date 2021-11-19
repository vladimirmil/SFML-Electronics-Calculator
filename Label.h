#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Label
{
private:
	sf::Font* font;
	sf::Text text;
public:
	Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color);
	virtual ~Label();

	void render(sf::RenderTarget* target);
};

#endif

