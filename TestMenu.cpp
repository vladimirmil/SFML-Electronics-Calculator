#include "TestMenu.h"

TestMenu::TestMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states) : State(window, ev, states)
{
	if (!this->states->empty())
	{
		this->states->back()->endState();
	}
	
	this->initGUI();
	std::cout << "Constuctor: TestMenu" << std::endl;
}

TestMenu::~TestMenu()
{
	std::cout << "Deconstuctor: TestMenu" << std::endl;

	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
	{
		std::cout << "Delete: Button" << std::endl;
		delete i->second;
	}
}

void TestMenu::initGUI()
{
	this->buttons["BUTTON_1"] = new Button(200.f, 100.f, 100.f, 30.f, &this->font, "page 1",
		sf::Color::Color(35, 31, 32, 255), sf::Color::Color(41, 36, 38, 255), sf::Color::Color(29, 26, 27, 255),
		sf::Color::Color(34, 30, 31, 255), 2);

	this->buttons["BUTTON_2"] = new Button(200.f, 150.f, 100.f, 30.f,&this->font, "button 2",
		sf::Color::Color(35, 31, 32, 255), sf::Color::Color(41, 36, 38, 255), sf::Color::Color(29, 26, 27, 255),
		sf::Color::Color(34, 30, 31, 255), 2);
}

void TestMenu::updateGUI()
{
	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}

	if (buttons["BUTTON_1"]->isPressed())
	{
		std::cout << "Button 1: pressed" << std::endl;
		this->states->push_front(new MainMenu(this->window, ev, states));		
	}

	if (buttons["BUTTON_2"]->isPressed())
	{
		std::cout << "Button 2: pressed" << std::endl;
	}
}

void TestMenu::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}
}

void TestMenu::endState()
{
	std::cout << "Ending state: TestClass" << std::endl;
	this->quit = true;
}

void TestMenu::update(/*const float& dt*/)
{

	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI(/*dt*/);
}

void TestMenu::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear(/*sf::Color(10, 20, 30, 255)*/);

	this->renderGUI(target);
	//this->window->clear(sf::Color(10, 20, 30, 255));
}
