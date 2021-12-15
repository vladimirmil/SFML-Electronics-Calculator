#include "PageMainMenu.h"


PageMainMenu::PageMainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages) : Page(window, ev, pages)
{
	if (!this->pages->empty())
	{
		this->pages->back()->endState();
	}

	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));

	this->initGUI();
}

PageMainMenu::~PageMainMenu()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	delete this->footer;
}

void PageMainMenu::endState()
{
	this->quit = true;
}

void PageMainMenu::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "Main menu");
	this->footer = new Footer(this->window, &this->font);

	this->buttons["BUTTON_PAGE1"] = new gui::Button(60.f, 100.f,  "Images/idle1.png", "Images/hover1.png", "Images/pressed1.png");
	this->buttons["BUTTON_PAGE2"] = new gui::Button(320.f, 100.f, "Images/idle2.png", "Images/hover2.png", "Images/pressed2.png");
	this->buttons["BUTTON_PAGE3"] = new gui::Button(580.f, 100.f, "Images/idle3.png", "Images/hover3.png", "Images/pressed3.png");
	this->buttons["BUTTON_PAGE4"] = new gui::Button(840.f, 100.f, "Images/idle4.png", "Images/hover4.png", "Images/pressed4.png");
}

void PageMainMenu::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	if (buttons["BUTTON_PAGE1"]->isReleased())
		this->pages->push_front(new Page1(this->window, ev, pages));

	if (buttons["BUTTON_PAGE2"]->isReleased())
		this->pages->push_front(new Page2(this->window, ev, pages));

	if (buttons["BUTTON_PAGE3"]->isReleased())
		this->pages->push_front(new Page3(this->window, ev, pages));

	if (buttons["BUTTON_PAGE4"]->isReleased())
		this->pages->push_front(new Page4(this->window, ev, pages));
}

void PageMainMenu::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void PageMainMenu::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}

void PageMainMenu::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void PageMainMenu::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);
}

void PageMainMenu::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
