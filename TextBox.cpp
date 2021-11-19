#include "TextBox.h"

void TextBox::initVariables()
{
	this->textboxState = TEXTBOX_IDLE;
	this->isSelected = false;
	this->width = 100;
	this->height = 25;
}

void TextBox::initShape(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color::Color(34, 30, 31, 255));
}

void TextBox::initText(sf::Font * font, std::string text)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(
		this->shape.getPosition().x + TEXT_OFFSET_X,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 3
	);
}

TextBox::TextBox(float x, float y, sf::Font * font, std::string text)
{
	this->initVariables();
	this->initShape(x,y);
	this->initText(font, text);
}

TextBox::~TextBox()
{
}

const bool TextBox::getPressed() const
{
	if (this->textboxState == TEXTBOX_PRESSED)
		return true;
	return false;
}

const bool TextBox::getSelected() const
{
	return this->isSelected;
}

void TextBox::updateText(sf::Event* ev)
{	
	switch (ev->type) {
	case sf::Event::TextEntered:
		if (this->isSelected && ev->text.unicode < 128)
		{
			std::cout << "ASCII character typed: " << static_cast<char>(ev->text.unicode) << std::endl;
		}
			
		break;
	default:
		break;
	}
}

void TextBox::update(sf::Vector2f mousePosition, sf::Event* ev)
{
	this->updateText(ev);

	if (this->getSelected()) {
		this->shape.setOutlineThickness(2);
		//this->shape.setOutlineColor(sf::Color::Color(250, 175, 0, 255));		//yellow/gold
		this->shape.setOutlineColor(sf::Color::Color(0, 93, 233, 255));	//blue
	}
	else {
		this->shape.setOutlineThickness(1);
		this->shape.setOutlineColor(sf::Color::Color(34, 30, 31, 255));
	}

	this->textboxState = TEXTBOX_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->textboxState = TEXTBOX_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = TEXTBOX_PRESSED;
			this->isSelected = true;
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = TEXTBOX_IDLE;
			this->isSelected = false;
		}
	}
	
}

void TextBox::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
