#include "PageFour.h"

void PageFour::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

PageFour::PageFour(sf::RenderWindow* window, sf::Event* ev, std::deque<State*>* states) : State(window, ev, states)
{
	if (!this->states->empty())
		this->states->back()->endState();

	this->inputX = { 20.f, 30.f, 35.f, 41.f, 88.f };
	this->inputY = { -5.f, 15.f, 25.f, 15.f, 10.f };
	
	this->initBackground(window);
	this->initGUI();
	std::cout << "Constuctor: TestMenu" << std::endl;
}

PageFour::~PageFour()
{
	std::cout << "Deconstuctor: TestMenu" << std::endl;

	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
	{
		std::cout << "Delete: Button" << std::endl;
		delete i->second;
	}

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
	{
		std::cout << "Delete: Textbox" << std::endl;
		delete i->second;
	}

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
	{
		std::cout << "Delete: Label" << std::endl;
		delete i->second;
	}

	for (auto i = this->graphs.begin(); i != this->graphs.end(); i++)
	{
		std::cout << "Delete: Graphs" << std::endl;
		delete i->second;
	}

	delete this->titlebar;
	delete this->footer;
}

void PageFour::updateInput()
{
	for (auto &i : this->textboxes)
	{
		i.second->updateText(this->ev);
	}
}

void PageFour::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}

void PageFour::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "Graph example");
	this->footer = new Footer(this->window, &this->font);

	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);
	this->buttons["BUTTON_UPDATE"] = new gui::Button(60.f, 334.f, "Update ", &this->font);

	this->graphs["GRAPH_1"] = new gui::Graph(&this->font, "Graph title", this->inputX, this->inputY, 490.f, 80.f, 570.f, 500.f, 25.f);

	this->textboxes["TEXTBOX_X"] = new gui::TextBox(60.f, 256.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_Y"] = new gui::TextBox(60.f, 281.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_TITLE"] = new gui::TextBox(60.f, 306.f, 156.f, &this->font, true);

	this->labels["LABEL_INFO"] = new gui::Label(60.f, 210.f, &this->font, "Separate input with spaces. If it contains a letter, it is ignored.", 12, sf::Color::White);
	this->labels["LABEL_X"] = new gui::Label(42.f, 256.f, &this->font, "X", 12, sf::Color::White);
	this->labels["LABEL_Y"] = new gui::Label(42.f, 281.f, &this->font, "Y", 12, sf::Color::White);
	this->labels["LABEL_TITLE"] = new gui::Label(28.f, 306.f, &this->font, "Title", 12, sf::Color::White);
}

void PageFour::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
	{
		i.second->update(this->mousePositionView);
	}

	for (auto &i : this->textboxes)
	{
		i.second->update(this->mousePositionView);
	}

	if (this->buttons["BUTTON_BACK"]->isPressed())
		this->states->push_front(new MainMenu(this->window, ev, states));

	if (this->buttons["BUTTON_UPDATE"]->isPressed())
	{
		this->inputX.clear();
		this->inputY.clear();
		std::string s1, s2, s3 = "";

		s1 = this->textboxes["TEXTBOX_X"]->getText();
		s2 = this->textboxes["TEXTBOX_Y"]->getText();
		s3 = this->textboxes["TEXTBOX_TITLE"]->getText();

		handleinput.stringToVectorFloat(this->inputX, s1, " ");
		handleinput.stringToVectorFloat(this->inputY, s2, " ");
		
		this->graphs["GRAPH_1"]->update(inputX, inputY, s3);
	}
}

void PageFour::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

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

	for (auto &i : this->graphs)
	{
		i.second->render(target);
	}
}

void PageFour::endState()
{
	std::cout << "Ending state: TestClass" << std::endl;
	this->quit = true;
}

void PageFour::update(/*const float& dt*/)
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI(/*dt*/);
}

void PageFour::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
	//this->window->clear(sf::Color(10, 20, 30, 255));
}
