#include "MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states) : State(window, ev, states)
{
	if (!this->states->empty())
	{
		this->states->back()->endState();
	}
	
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

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
	{
		std::cout << "Delete: TextBox" << std::endl;
		delete i->second;
	}

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
	{
		std::cout << "Delete: Label" << std::endl;
		delete i->second;
	}
}

void MainMenu::initGUI()
{
	this->buttons["BUTTON_1"] = new Button(100.f, 100.f, 100.f, 30.f, &this->font, "page 2",
		BLUE_IDLE, BLUE_HOVER, BLUE_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);
		//YELLOW_IDLE, YELLOW_HOVER, YELLOW_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);
	
	this->buttons["BUTTON_2"] = new Button(100.f, 150.f, 100.f, 30.f, &this->font, "button 2",
		BLUE_IDLE, BLUE_HOVER, BLUE_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);
		//YELLOW_IDLE, YELLOW_HOVER, YELLOW_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);
	this->buttons["BUTTON_3"] = new Button(100.f, 200.f, 100.f, 30.f, &this->font, "button 3",
		BLUE_IDLE, BLUE_HOVER, BLUE_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);
		//YELLOW_IDLE, YELLOW_HOVER, YELLOW_PRESSED, sf::Color::Color(34, 30, 31, 255), 2.f);

	this->textboxes["textbox1"] = new TextBox(100.f, 250.f, &this->font, "textbox1");
	this->textboxes["textbox2"] = new TextBox(100.f, 290.f, &this->font, "textbox2");
	this->textboxes["textbox3"] = new TextBox(100.f, 330.f, &this->font, "textbox3");

	this->labels["label1"] = new Label(50.f, 255.f, &this->font, "Label1", 12, sf::Color::White);
	this->labels["label2"] = new Label(50.f, 295.f, &this->font, "Label2", 12, sf::Color::White);
	this->labels["label3"] = new Label(50.f, 335.f, &this->font, "Label3", 12, sf::Color::White);
}

void MainMenu::updateGUI()
{
	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}
	for (auto &i : this->textboxes)
	{
		i.second->update(this->mousePositionView, this->ev);
	}

	if (buttons["BUTTON_1"]->isPressed())
	{
		std::cout << "Button 1: pressed" << std::endl;
		this->states->push_front(new TestMenu(this->window, ev, states));
	}
		
	if (buttons["BUTTON_2"]->isPressed())
	{
		std::cout << "Button 2: pressed" << std::endl;
	}
		
	if (buttons["BUTTON_3"]->isPressed())
	{
		std::cout << "Button 3: pressed" << std::endl;
	}
		
}

void MainMenu::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	for (auto &i : this->textboxes)
	{
		i.second->render(target);
	}
	for (auto &i : this->labels)
	{
		i.second->render(target);
	}
	
}

void MainMenu::endState()
{
	std::cout << "Ending state: MainMenu" << std::endl;
	this->quit = true;
}

void MainMenu::update(/*const float& dt*/)
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI(/*dt*/);
}

void MainMenu::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	//target->clear(sf::Color(39, 34, 36, 255));
	target->clear(sf::Color(35, 31, 32, 255));

	//target->draw(this->background);
	this->renderGUI(target);
	//this->window->clear(sf::Color(10, 20, 30, 255));
}
