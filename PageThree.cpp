#include "PageThree.h"

void PageThree::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

PageThree::PageThree(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states) : State(window, ev, states)
{
	if (!this->states->empty())
		this->states->back()->endState();

	this->initBackground(window);
	this->initGUI();
	std::cout << "Constuctor: TestMenu" << std::endl;
}

PageThree::~PageThree()
{
	std::cout << "Deconstuctor: TestMenu" << std::endl;

	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
	{
		std::cout << "Delete: Button" << std::endl;
		delete i->second;
	}

	delete this->titlebar;
	delete this->footer;
}

void PageThree::updateInput()
{
}

void PageThree::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}

void PageThree::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "Page 3");
	this->footer = new Footer(this->window, &this->font);
	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);
}

void PageThree::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}

	if (buttons["BUTTON_BACK"]->isPressed())
		this->states->push_front(new MainMenu(this->window, ev, states));
}

void PageThree::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}
}

void PageThree::endState()
{
	std::cout << "Ending state: TestClass" << std::endl;
	this->quit = true;
}

void PageThree::update(/*const float& dt*/)
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI(/*dt*/);
}

void PageThree::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
