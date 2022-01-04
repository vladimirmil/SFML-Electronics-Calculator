#include "Page4.h"


void Page4::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

Page4::Page4(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages) : Page(window, ev, pages)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->initBackground(window);
	this->initGUI();
}

Page4::~Page4()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;
}

void Page4::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void Page4::initGUI()
{
	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);

	this->labels["LABEL_EMPTY"] = new gui::Label(540.f, 320.f, &this->font, "Page 4", 12, sf::Color::White);
}

void Page4::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	if (buttons["BUTTON_BACK"]->isReleased())
		this->pages->push_front(new PageMain(this->window, ev, pages));
}

void Page4::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);
}

void Page4::endState()
{
	this->quit = true;
}

void Page4::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void Page4::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
