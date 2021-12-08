#include "Application.h"
#include "MainMenu.h"

void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initWindow()
{
	this->hasFocus = true;
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;
	this->window = new sf::RenderWindow(this->videoMode, "title", sf::Style::None);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(FRAMERATE_LIMIT);
	this->window->setVerticalSyncEnabled(true);
}

void Application::initStates()
{
	this->states.push_front(new MainMenu(this->window, &this->ev, &this->states));
}

Application::Application()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

Application::~Application()
{
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
		case sf::Event::GainedFocus:
			this->hasFocus = true;
			break;

		case sf::Event::LostFocus:
			this->hasFocus = false;
			break;

		case sf::Event::TextEntered:
			if (!this->states.empty() && this->hasFocus)
				this->states.front()->updateInput();
			break;
		case sf::Event::MouseMoved:
			if (!this->states.empty() && this->hasFocus)
				this->states.front()->updateMouseMov();
			break;
		
		case sf::Event::MouseButtonReleased:
			if (!this->states.empty() && this->hasFocus)
				this->states.front()->updateInput();
			break;
		
		case sf::Event::Closed:
			this->window->close();
			break;
		default:
			break;
		}
	}
}


void Application::update()
{
	this->pollEvents();

	if (!this->states.empty())
	{
		if (this->hasFocus)
			this->states.front()->update();

		if (this->states.back()->getQuit())
		{
			delete this->states.back();
			this->states.pop_back();
		}		
	}
	else
		this->window->close();
		// No more states
		
}

void Application::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.front()->render(this->window);
	this->window->display();
}

void Application::run()
{
	while (this->isRunning())
	{
		this->update();
		this->render();
	}
}