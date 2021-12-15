#include "Footer.h"

Footer::Footer(sf::RenderWindow* window, sf::Font* font)
{
	this->shape.setSize(sf::Vector2f((float)window->getSize().x, 20));
	this->shape.setPosition(sf::Vector2f(0, 620));
	this->shape.setFillColor(sf::Color::Color(30, 30, 30, 255));

	this->font = font;
	this->author.setFont(*this->font);
	this->author.setString(sAuthor);
	this->author.setCharacterSize(10);
	this->author.setFillColor(sf::Color::Color(60, 60, 60, 255));
	this->author.setPosition(5,625);

	this->version.setFont(*this->font);
	this->version.setString(sVersion);
	this->version.setCharacterSize(10);
	this->version.setFillColor(sf::Color::Color(60, 60, 60, 255));
	this->version.setPosition(1075, 625);
}

Footer::~Footer()
{
}

void Footer::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->author);
	target->draw(this->version);
}
