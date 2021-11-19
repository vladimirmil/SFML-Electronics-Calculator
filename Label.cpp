#include "Label.h"

Label::Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setPosition(x, y);
}

Label::~Label()
{
}

void Label::render(sf::RenderTarget * target)
{
	target->draw(this->text);
}
