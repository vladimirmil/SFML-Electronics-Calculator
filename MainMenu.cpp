#include "MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states) : State(window, ev, states)
{
	if (!this->states->empty())
	{
		this->states->back()->endState();
	}

	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));

	this->initGUI();
	std::cout << "Constuctor: MainMenu" << std::endl;	
}

MainMenu::~MainMenu()
{
	std::cout << "Deconstuctor: MainMenu" << std::endl;
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
	{
		std::cout << "Delete: Button" << std::endl;
		delete i->second;
	}

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
	{
		std::cout << "Delete: Label" << std::endl;
		delete i->second;
	}
	delete this->footer;
}

void MainMenu::endState()
{
	std::cout << "Ending state: MainMenu" << std::endl;
	this->quit = true;
}

void MainMenu::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "Main menu");
	this->footer = new Footer(this->window, &this->font);

	this->buttons["BUTTON_PAGE1"] = new gui::Button(60.f, 100.f, "Images/page1ButtonIdle.png", "Images/page1ButtonHover.png", "Images/page1ButtonPressed.png");
	this->buttons["BUTTON_PAGE2"] = new gui::Button(320.f, 100.f, "Images/page2ButtonIdle.png", "Images/page2ButtonHover.png", "Images/page2ButtonPressed.png");
	this->buttons["BUTTON_PAGE3"] = new gui::Button(580.f, 100.f, "Images/page3ButtonIdle.png", "Images/page3ButtonHover.png", "Images/page3ButtonPressed.png");
	this->buttons["BUTTON_PAGE4"] = new gui::Button(840.f, 100.f, "Images/page4ButtonIdle.png", "Images/page4ButtonHover.png", "Images/page4ButtonPressed.png");
}

void MainMenu::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}

	if (buttons["BUTTON_PAGE1"]->isPressed())
		this->states->push_front(new PageOne(this->window, ev, states));
	if (buttons["BUTTON_PAGE2"]->isPressed())
		this->states->push_front(new PageTwo(this->window, ev, states));
	if (buttons["BUTTON_PAGE3"]->isPressed())
		this->states->push_front(new PageThree(this->window, ev, states));
	if (buttons["BUTTON_PAGE4"]->isPressed())
		this->states->push_front(new PageFour(this->window, ev, states));	
}

void MainMenu::updateInput()
{
}

void MainMenu::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}

void MainMenu::update(/*const float& dt*/)
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI(/*dt*/);
}

void MainMenu::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	for (auto &i : this->labels)
	{
		i.second->render(target);
	}
}

void MainMenu::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
