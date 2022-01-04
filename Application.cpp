#include "Application.h"
#include "PageMain.h"

void Application::initVariables()
{
	this->window = nullptr;
}

void Application::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
	{
		throw("ERROR: Coudld not load font");
	}
}

void Application::initWindow()
{
	this->hasFocus = true;
	this->videoMode.height = WINDOW_HEIGHT;
	this->videoMode.width = WINDOW_WIDTH;
	this->window = new sf::RenderWindow(this->videoMode, "Electronics Calculator", sf::Style::None);
	this->window->setKeyRepeatEnabled(false);
	this->window->setFramerateLimit(FRAMERATE_LIMIT);
	this->window->setVerticalSyncEnabled(true);
}

void Application::initStates()
{
	this->pages.push_front(new PageMain(this->window, &this->ev, &this->pages));
}


Application::Application()
{
	this->initVariables();
	this->initFonts();
	this->initWindow();
	this->initStates();

	this->titlebar = new Titlebar(this->window, &this->font, "Electronics Calculator");
	this->footer = new Footer(this->window, &this->font);
}

Application::~Application()
{
	while (!this->pages.empty())
	{
		delete this->pages.front();
		this->pages.pop_front();
	}

	delete this->titlebar;
	delete this->footer;

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
			this->titlebar->updateWindowPosition(this->window);
			break;
		
		case sf::Event::MouseButtonReleased:
			this->titlebar->updateInput(&this->ev, this->mousePositionView);
			this->titlebar->setPressed(false);

			if (!this->pages.empty() && this->hasFocus)
				this->pages.front()->updateInput();
			break;

		case sf::Event::MouseButtonPressed:
			this->titlebar->updateMouse(this->window, &this->ev, this->mousePositionView);
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
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->pollEvents();

	if (this->hasFocus)
		this->titlebar->update(this->mousePositionView, this->window);

	if (!this->pages.empty())
	{
		//if (this->hasFocus)
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

	this->titlebar->render(this->window);
	this->footer->render(this->window);
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