#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->buttonState = BUTTON_IDLE;
	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;

	this->shape.setPosition(sf::Vector2f(x,y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineColor(this->outlineColor);
	this->shape.setOutlineThickness(this->outlineThickness);
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(14);
	this->text.setPosition(
		this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height/ 2.f - 3
	);
}

Button::~Button()
{

}

const bool Button::isPressed()
{
	if (this->buttonState == BUTTON_PRESSED)
		return true;
	return false;
}


void Button::update(sf::Vector2f mousePosition)
{
	this->buttonState = BUTTON_IDLE;
	
	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = BUTTON_PRESSED;
	}

	switch (buttonState)
	{
	case BUTTON_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BUTTON_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BUTTON_PRESSED:
		this->shape.setFillColor(this->pressedColor);
		break;
	default:
		this->shape.setFillColor(this->idleColor);
		break;
	}
}


void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}
