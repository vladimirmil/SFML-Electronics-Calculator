#include "Titlebar.h"

Titlebar::Titlebar(sf::RenderWindow* window, sf::Font * font)
{
	this->isPressed = false;

	this->shape.setSize(sf::Vector2f((float)window->getSize().x, 40));
	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setFillColor(sf::Color::Color(33, 33, 33, 255));

	this->font = font;
	this->title.setFont(*this->font);

	this->exitButton = new gui::Button(1048, 5, 30.f, 30.f, this->font, "X", sf::Color::Color(33, 33, 33, 255), 
		sf::Color::Color(245, 54, 5, 255), sf::Color::Color(213, 47, 4, 255), sf::Color::Black, 0.f);
}

Titlebar::Titlebar(sf::RenderWindow* window, sf::Font * font, std::string title)
{
	this->isPressed = false;

	this->shape.setSize(sf::Vector2f((float)window->getSize().x, 40));
	this->shape.setPosition(sf::Vector2f(0, 0));
	this->shape.setFillColor(sf::Color::Color(33, 33, 33, 255));

	this->font = font;
	this->title.setFont(*this->font);
	this->title.setCharacterSize(12);
	this->title.setString(title);
	this->title.setFillColor(sf::Color::White);
	this->title.setPosition((float)window->getSize().x / 2.f - (int)this->title.getGlobalBounds().width / 2, 15);

	this->exitButton = new gui::Button(1048, 5, 30.f, 30.f, this->font, "X", sf::Color::Color(33, 33, 33, 255),
		sf::Color::Color(245, 54, 5, 255), sf::Color::Color(213, 47, 4, 255), sf::Color::Black, 0.f);
}


Titlebar::~Titlebar()
{
	delete this->exitButton;
}

void Titlebar::setPressed(bool value)
{
	this->isPressed = value;
}

const bool Titlebar::getPressed()
{
	if (this->isPressed)
		return true;
	return false;
}

void Titlebar::updateWindowPosition(sf::RenderWindow* window)
{
	if (this->getPressed())
		window->setPosition(sf::Mouse::getPosition() + this->grabbedOffset);
}

void Titlebar::update(sf::Vector2f mousePosition, sf::RenderWindow* window)
{
	if (this->shape.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->setPressed(true);
		this->grabbedOffset = window->getPosition() - sf::Mouse::getPosition();
	}
	else
	{
		this->setPressed(false);
	}

	this->exitButton->update(mousePosition);
	if (this->exitButton->isPressed())
		window->close();
}

void Titlebar::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	this->exitButton->render(target);
	target->draw(this->title);
}
