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

	this->popup_text = 
"Yo, this is test text to see how this works.\n\
New line dude, it supports the fuck out of new lines.\n\
How does it look like?\n\
Yo, fourth line..\n\
What do I even write anymore?????";

	this->popup_text2 =
"This line is so long, like realy long. Have you seen any line that is longer than this\n\
Yo, second line again. It works it seems but I don't know what to write anymore.\n\
Third line tho. Let's goooooo\n\
this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));\n\
this->background.setFillColor(sf::Color(37, 37, 37, 255));\n\
this->initBackground(window);\n\
this->initGUI();";

	this->initBackground(window);
	this->initGUI();
}

PageThree::~PageThree()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;
/*
	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;
*/
	for (auto i = this->popups.begin(); i != this->popups.end(); i++)
		delete i->second;

	delete this->titlebar;
	delete this->footer;
}

void PageThree::updateInput()
{
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
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
	this->buttons["BUTTON_POPUP_1"] = new gui::Button(30.f, 560.f, "PopUp 1", &this->font);
	this->buttons["BUTTON_POPUP_2"] = new gui::Button(330.f, 560.f, "PopUp 2", &this->font);
	this->buttons["BUTTON_POPUP_3"] = new gui::Button(530.f, 560.f, "PopUp 3", &this->font);

	//this->labels["LABEL_EMPTY"] = new gui::Label(540.f, 320.f, &this->font, "Empty", 12, sf::Color::White);

	this->popups["POPUP_TEST_1"] = new gui::PopUp(&this->font, this->popup_text, 100.f, 100.f);
	this->popups["POPUP_TEST_2"] = new gui::PopUp(&this->font, this->popup_text2, 500.f, 100.f);
	this->popups["POPUP_TEST_3"] = new gui::PopUp(&this->font, "       ", 250.f, 300.f);
}

void PageThree::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->popups)
		i.second->update(this->mousePositionView);
		
	if (buttons["BUTTON_BACK"]->isReleased())
		this->states->push_front(new MainMenu(this->window, ev, states));

	if (buttons["BUTTON_POPUP_1"]->isReleased())
		this->popups["POPUP_TEST_1"]->setVisibility(!this->popups["POPUP_TEST_1"]->getVisibility());

	if (buttons["BUTTON_POPUP_2"]->isReleased())
		this->popups["POPUP_TEST_2"]->setVisibility(!this->popups["POPUP_TEST_2"]->getVisibility());

	if (buttons["BUTTON_POPUP_3"]->isReleased())
		this->popups["POPUP_TEST_3"]->setVisibility(!this->popups["POPUP_TEST_3"]->getVisibility());
}

void PageThree::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->buttons)
		i.second->render(target);
/*
	for (auto &i : this->labels)
		i.second->render(target);
*/
	for (auto &i : this->popups)
	{
		if (i.second->getVisibility())
			i.second->render(target);
	}	
}

void PageThree::endState()
{
	this->quit = true;
}

void PageThree::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void PageThree::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
