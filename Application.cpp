#include "Application.h"
#include "MainMenu.h"
#include "TestMenu.h"

void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initWindow()
{
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;
	this->window = new sf::RenderWindow(this->videoMode, "title", sf::Style::Default);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(FRAMERATE_LIMIT);
}

void Application::initStates()
{
	this->states.push_front(new MainMenu(this->window, &this->ev, &this->states));
}

Application::Application()
{
	std::cout << "Constuctor: Application" << std::endl;
	this->initVariables();
	this->initWindow();
	this->initStates();
}

Application::~Application()
{
	std::cout << "Deconstuctor: Application" << std::endl;
	while (!this->states.empty())
	{
		delete this->states.front();
		this->states.pop_front();
	}
	delete this->window;
}

const bool Application::isRunning() const
{
	return this->window->isOpen();
}

void Application::pollEvents()
{
	
	while (this->window->pollEvent(this->ev))
	{
		
		switch (this->ev.type)
		{
		/*
		case sf::Event::TextEntered:
			break;
		*/
		case sf::Event::Closed:
			this->window->close();
			break;
		default:
			break;
		}
	}
}
/*
void Application::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}
*/

void Application::update(/*const float& dt*/)
{
	this->pollEvents();

	if (!this->states.empty())
	{
		this->states.front()->update();

		if (this->states.back()->getQuit())
		{
			delete this->states.back();
			this->states.pop_back();
		}		
	}
	else
	{
		std::cout << "No more states" << std::endl;
		this->window->close();
	}
}

void Application::render()
{
	this->window->clear(sf::Color(255, 255, 255, 255));

	if (!this->states.empty())
		this->states.front()->render(this->window);
	this->window->display();
}

void Application::run()
{
	while (this->isRunning())
	{
		//this->updateDt();
		this->update(/*this->dt*/);
		this->render();
	}
}