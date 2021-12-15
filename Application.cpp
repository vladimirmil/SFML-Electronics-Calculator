#include "Application.h"
#include "PageMainMenu.h"

void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initWindow()
{
	this->hasFocus = true;
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;
	this->window = new sf::RenderWindow(this->videoMode, "Yo", sf::Style::None);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(FRAMERATE_LIMIT);
	this->window->setVerticalSyncEnabled(true);
}

void Application::initStates()
{
	this->pages.push_front(new PageMainMenu(this->window, &this->ev, &this->pages));
}

Application::Application()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

Application::~Application()
{
	while (!this->pages.empty())
	{
		delete this->pages.front();
		this->pages.pop_front();
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
			if (!this->pages.empty() && this->hasFocus)
				this->pages.front()->updateInput();
			break;
		case sf::Event::MouseMoved:
			if (!this->pages.empty() && this->hasFocus)
				this->pages.front()->updateMouseMov();
			break;
		
		case sf::Event::MouseButtonReleased:
			if (!this->pages.empty() && this->hasFocus)
				this->pages.front()->updateInput();
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

	if (!this->pages.empty())
	{
		if (this->hasFocus)
			this->pages.front()->update();

		if (this->pages.back()->getQuit())
		{
			delete this->pages.back();
			this->pages.pop_back();
		}		
	}
	else
		this->window->close();
		// No more states
		
}

void Application::render()
{
	this->window->clear();

	if (!this->pages.empty())
		this->pages.front()->render(this->window);
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