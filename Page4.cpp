#include "Page4.h"

void Page4::initPopUpText()
{
	this->popuptext.append("Separate points with spaces. If a point contains a letter, it is ignored.\n\n");
	this->popuptext.append("X: 10 23 34\nY: 132 180 202\nTitle: Graph title");
}

void Page4::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

Page4::Page4(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages) : Page(window, ev, pages)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->inputX = { 10.f, 23.f, 34.f };
	this->inputY = { 132.f, 180.f, 202.f };
	this->initPopUpText();
	this->initBackground(window);
	this->initGUI();
}

Page4::~Page4()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->graphs.begin(); i != this->graphs.end(); i++)
		delete i->second;

	for (auto i = this->popups.begin(); i != this->popups.end(); i++)
		delete i->second;

	delete this->titlebar;
	delete this->footer;
}

void Page4::updateInput()
{
	for (auto &i : this->textboxes)
		i.second->updateText(this->ev);

	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void Page4::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}

void Page4::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "Graph example");
	this->footer = new Footer(this->window, &this->font);

	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);
	this->buttons["BUTTON_UPDATE"] = new gui::Button(60.f, 195.f, "Update ", &this->font);
	this->buttons["BUTTON_HELP"] = new gui::Button(160.f, 195.f, 25.f, 25.f, "?", &this->font);

	this->buttons["BUTTON_COLOR_1"] = new gui::Button(60.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color(235,0,0,255), sf::Color::Color(245, 0, 0, 255), sf::Color::Color(255, 0, 0, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_2"] = new gui::Button(80.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color::Color(0, 235, 0, 255), sf::Color::Color(0, 245, 0, 255), sf::Color::Color(0, 255, 0, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_3"] = new gui::Button(100.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color(0, 0, 235, 255), sf::Color::Color(0, 0, 245, 255), sf::Color::Color(0, 0, 255, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_4"] = new gui::Button(120.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color(255, 255, 51, 255), sf::Color::Color(255, 255, 51, 255), sf::Color::Color(255, 255, 51, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_5"] = new gui::Button(140.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color(255, 190, 7, 255), sf::Color::Color(255, 190, 7, 255), sf::Color::Color(255, 190, 7, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_6"] = new gui::Button(160.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color::Magenta, sf::Color::Color::Magenta, sf::Color::Color::Magenta, sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_7"] = new gui::Button(180.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color(80, 80, 80, 255), sf::Color::Color(80, 80, 80, 255), sf::Color::Color(80, 80, 80, 255), sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_8"] = new gui::Button(200.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color::Black, sf::Color::Color::Black, sf::Color::Color::Black, sf::Color::Color::Red, 0.f);
	this->buttons["BUTTON_COLOR_9"] = new gui::Button(220.f, 240.f, 15.f, 15.f, &this->font, "",
		sf::Color::Color::White, sf::Color::Color::White, sf::Color::Color::White, sf::Color::Color::Red, 0.f);
	

	this->popups["POPUP"] = new gui::PopUp(&this->font, this->popuptext, 580.f, 250.f);

	this->graphs["GRAPH_1"] = new gui::Graph(&this->font, "Graph title", this->inputX, this->inputY, 490.f, 80.f, 570.f, 500.f, 25.f);

	this->textboxes["TEXTBOX_X"] = new gui::TextBox(60.f, 120.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_Y"] = new gui::TextBox(60.f, 145.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_TITLE"] = new gui::TextBox(60.f, 170.f, 156.f, &this->font, true);

	this->labels["LABEL_X"] = new gui::Label(42.f, 120.f, &this->font, "X", 12, sf::Color::White);
	this->labels["LABEL_Y"] = new gui::Label(42.f, 145.f, &this->font, "Y", 12, sf::Color::White);
	this->labels["LABEL_TITLE"] = new gui::Label(28.f, 170.f, &this->font, "Title", 12, sf::Color::White);
}

void Page4::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->update(this->mousePositionView);

	for (auto &i : this->popups)
		i.second->update(this->mousePositionView);

	if (this->buttons["BUTTON_BACK"]->isReleased())
		this->pages->push_front(new PageMainMenu(this->window, ev, pages));

	if (this->buttons["BUTTON_UPDATE"]->isReleased())
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

	if (buttons["BUTTON_HELP"]->isReleased())
		this->popups["POPUP"]->setVisibility(!this->popups["POPUP"]->getVisibility());
	if (buttons["BUTTON_COLOR_1"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(235, 0, 0, 255));
	if (buttons["BUTTON_COLOR_2"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(0, 235, 0, 255));
	if (buttons["BUTTON_COLOR_3"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(0, 0, 235, 255));
	if (buttons["BUTTON_COLOR_4"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(255, 255, 51, 255));
	if (buttons["BUTTON_COLOR_5"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(255, 190, 7, 255));
	if (buttons["BUTTON_COLOR_6"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color::Magenta);
	if (buttons["BUTTON_COLOR_7"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color(80, 80, 80, 255));
	if (buttons["BUTTON_COLOR_8"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color::Black);
	if (buttons["BUTTON_COLOR_9"]->isReleased())
		this->graphs["GRAPH_1"]->setColor(sf::Color::Color::White);
}

void Page4::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->textboxes)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->graphs)
		i.second->render(target);

	for (auto &i : this->popups)
	{
		if (i.second->getVisibility())
			i.second->render(target);
	}
}

void Page4::endState()
{
	this->quit = true;
}

void Page4::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void Page4::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
