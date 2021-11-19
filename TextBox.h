#ifndef TEXTBOX_H
#define TEXTBOS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>

constexpr auto TEXT_OFFSET_X = 5;

enum textbox_state {
	TEXTBOX_IDLE,
	TEXTBOX_HOVER,
	TEXTBOX_PRESSED,
};

class TextBox
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	float width;
	float height;
	bool isSelected;
	short unsigned textboxState;

	void initVariables();
	void initShape(float x, float y);
	void initText(sf::Font * font, std::string text);
	
public:
	TextBox(float x, float y, sf::Font * font, std::string text);
	virtual ~TextBox();

	const bool getPressed() const;
	const bool getSelected() const;

	void updateText(sf::Event* ev);
	void update(sf::Vector2f mousePosition, sf::Event* ev);
	void render(sf::RenderTarget* target);
};

#endif // !TEXTBOX_H



