#include "State.h"

State::State(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states)
{
	std::cout << "Constuctor: State" << std::endl;
	this->window = window;
	this->ev = ev;
	this->quit = false;
	this->initFonts();
	this->states = states;
}

State::~State()
{
	std::cout << "Deconstuctor: State" << std::endl;
}

const bool & State::getQuit() const
{
	return this->quit;
}

void State::setQuit(bool quit)
{
	this->quit = quit;
}

void State::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Regular.ttf"))
	{
		throw("ERROR: Coudld not load font");
	}
}

void State::checkQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePositionScreen = sf::Mouse::getPosition();
	this->mousePositionWindow = sf::Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
