#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

enum button_state {
	BUTTON_IDLE,
	BUTTON_PRESSED,
	BUTTON_HOVER,
};

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
	sf::Color outlineColor;
	float outlineThickness;
	short unsigned buttonState;

public:
	Button(float x, float y, float width, float height,
		sf::Font* font,std::string text, sf::Color idleColor, sf::Color hoverColor, 
		sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
	virtual ~Button();

	const bool isPressed();
	void update(sf::Vector2f mousePosition);
	void render(sf::RenderTarget* target);
};

#endif // !BUTTON_H



