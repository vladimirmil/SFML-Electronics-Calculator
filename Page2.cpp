#include "Page2.h"

void Page2::initPopUpText()
{
	this->popup1text.append("Non-inverting BJT voltage level shift\n\n");
	this->popup1text.append("Valid prefixes: G, M, K, m, u, n, p");

	this->popup2text.append("Inverting BJT voltage level shift\n\n");
	this->popup2text.append("Valid prefixes: G, M, K, m, u, n, p");
}

void Page2::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

Page2::Page2(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages) : Page(window, ev, pages)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->calculateState = this->CALC_STATE_0;
	this->initPopUpText();
	this->initBackground(window);
	this->initGUI();
}

Page2::~Page2()
{
	for (auto i = this->buttons.begin(); i != this->buttons.end(); i++)
		delete i->second;

	for (auto i = this->textboxes.begin(); i != this->textboxes.end(); i++)
		delete i->second;

	for (auto i = this->labels.begin(); i != this->labels.end(); i++)
		delete i->second;

	for (auto i = this->images.begin(); i != this->images.end(); i++)
		delete i->second;

	for (auto i = this->popups.begin(); i != this->popups.end(); i++)
		delete i->second;

	delete this->titlebar;
	delete this->footer;
}

void Page2::calculate(calculate_state calculateState)
{
	double vi, vo, ic1, ic2, hfe, vbe, vce, r1, r2, r3, v, ib1, ib2, ie1, ie2 = 0;

	switch (calculateState)
	{
	case this->CALC_STATE_0:
		break;
		/******************************************************************************************************/
	case this->CALC_STATE_1:

		/****************************
			example				
			vi = 3.f;				
			vo = 5.f;				
			ic1 = 0.001f;			
			ic2 = 0.001f;			
			hfe = 100.f;			
			vbe = 0.648f;			
			vce = 0.041f;			
		****************************/
		vi = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VI"]->getText());
		vo = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VO"]->getText());
		ic1 = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_IC1"]->getText());
		ic2 = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_IC2"]->getText());
		vbe = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VBE"]->getText());
		vce = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VCE"]->getText());
		hfe = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_HFE"]->getText());

		v = vo;
		//	r2 = (v - vce) / ic1;
		try { r2 = handleinput.divisionException((v - vce), ic1); }
		catch (std::invalid_argument &e) 
		{
			r2 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	ib1 = (5 * ic1) / hfe;
		try { ib1 = handleinput.divisionException((5 * ic1), hfe); }
		catch (std::invalid_argument &e)
		{
			ib1 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	r1 = (vi - vbe) / ib1;
		try { r1 = handleinput.divisionException((vi - vbe), ib1); }
		catch (std::invalid_argument &e)
		{
			r1 = -1;
			std::cerr << e.what() << std::endl;
		}
		ie1 = ib1 + ic1;
		//	ib2 = (5 * ic2) / hfe;
		try { ib2 = handleinput.divisionException((5 * ic2), hfe); }
		catch (std::invalid_argument &e) 
		{
			ib2 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	r3 = (vo - vce) / ic2;
		try { r3 = handleinput.divisionException((vo - vce), ic2); }
		catch (std::invalid_argument &e) 
		{
			r3 = -1;
			std::cerr << e.what() << std::endl;
		}

		textboxes["TEXTBOX_1_O1_R1"]->setText(handleinput.toString(r1));
		textboxes["TEXTBOX_1_O1_R2"]->setText(handleinput.toString(r2));
		textboxes["TEXTBOX_1_O1_R3"]->setText(handleinput.toString(r3));
		textboxes["TEXTBOX_1_O1_V"]->setText(handleinput.toString(v));

		textboxes["TEXTBOX_1_O1_IB1"]->setText(handleinput.toString(ib1));
		textboxes["TEXTBOX_1_O1_IB2"]->setText(handleinput.toString(ib2));
		break;
		/******************************************************************************************************/
	case this->CALC_STATE_2:

		vi = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VI"]->getText());
		vo = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VO"]->getText());
		vbe = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VBE"]->getText());
		vce = handleinput.getDouble(this->textboxes["TEXTBOX_1_I1_VCE"]->getText());
		r1 = handleinput.getDouble(this->textboxes["TEXTBOX_1_I2_R1"]->getText());
		r2 = handleinput.getDouble(this->textboxes["TEXTBOX_1_I2_R2"]->getText());
		r3 = handleinput.getDouble(this->textboxes["TEXTBOX_1_I2_R3"]->getText());
		//	ib1 = (vi - vbe) / r1;
		try { ib1 = handleinput.divisionException((vi - vbe), r1); }
		catch (std::invalid_argument &e)
		{
			ib1 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	ic1 = (vo - vce) / r2;
		try { ic1 = handleinput.divisionException((vo - vce), r2); }
		catch (std::invalid_argument &e)
		{
			ic1 = -1;
			std::cerr << e.what() << std::endl;
		}
		ie1 = ib1 + ic1;
		//	ib2 = (vo - vbe) / r2;
		try { ib2 = handleinput.divisionException((vo - vbe), r2); }
		catch (std::invalid_argument &e)
		{
			ib2 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	ic2 = (vo - vce) / r3;
		try { ic2 = handleinput.divisionException((vo - vce), r3); }
		catch (std::invalid_argument &e)
		{
			ic2 = -1;
			std::cerr << e.what() << std::endl;
		}
		ie2 = ib2 + ic2;

		textboxes["TEXTBOX_1_O2_IB1"]->setText(handleinput.toString(ib1));
		textboxes["TEXTBOX_1_O2_IB2"]->setText(handleinput.toString(ib2));
		textboxes["TEXTBOX_1_O2_IC1"]->setText(handleinput.toString(ic1));
		textboxes["TEXTBOX_1_O2_IC2"]->setText(handleinput.toString(ic2));
		textboxes["TEXTBOX_1_O2_IE1"]->setText(handleinput.toString(ie1));
		textboxes["TEXTBOX_1_O2_IE2"]->setText(handleinput.toString(ie2));
		break;
		/******************************************************************************************************/
	case this->CALC_STATE_3:
		
		/****************************
			example					
			vi = 3.f;				
			vo = 5.f;				
			ic1 = 0.001f;			
			hfe = 100.f;			
			vbe = 0.648f;			
			vce = 0.041f;			
		****************************/

		vi = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VI"]->getText());
		vo = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VO"]->getText());
		ic1 = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_IC"]->getText());
		vbe = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VBE"]->getText());
		vce = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VCE"]->getText());
		hfe = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_HFE"]->getText());

		v = vo;
		//	ib1 = (5 * ic1) / hfe;
		try { ib1 = handleinput.divisionException((5 * ic1), hfe); }
		catch (std::invalid_argument &e)
		{
			ib1 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	r1 = (vi - vbe) / ib1;
		try { r1 = handleinput.divisionException((vi - vbe), ib1); }
		catch (std::invalid_argument &e)
		{
			r1 = -1;
			std::cerr << e.what() << std::endl;
		}
		//	r2 = (v - vce) / ic1;
		try { r2 = handleinput.divisionException((v - vce), ic1); }
		catch (std::invalid_argument &e)
		{
			r2 = -1;
			std::cerr << e.what() << std::endl;
		}
		
		textboxes["TEXTBOX_2_O1_R1"]->setText(handleinput.toString(r1));
		textboxes["TEXTBOX_2_O1_R2"]->setText(handleinput.toString(r2));
		textboxes["TEXTBOX_2_O1_V"]->setText(handleinput.toString(v));
		textboxes["TEXTBOX_2_O1_IB"]->setText(handleinput.toString(ib1));
		break;
		/******************************************************************************************************/
	case this->CALC_STATE_4:

		vi = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VI"]->getText());
		vo = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VO"]->getText());
		vbe = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VBE"]->getText());
		vce = handleinput.getDouble(this->textboxes["TEXTBOX_2_I1_VCE"]->getText());
		r1 = handleinput.getDouble(this->textboxes["TEXTBOX_2_I2_R1"]->getText());
		r2 = handleinput.getDouble(this->textboxes["TEXTBOX_2_I2_R2"]->getText());

		v = vo;
		//	ib1 = (vi - vbe) / r1
		try { ib1 = handleinput.divisionException((vi - vbe), r1); }
		catch (std::invalid_argument &e)
		{
			ib1 = -1;
			std::cerr << e.what() << std::endl;
		}
        //	ic1 = (v - vce) / r2
		try { ic1 = handleinput.divisionException((v - vce), r2); }
		catch (std::invalid_argument &e)
		{
			ic1 = -1;
			std::cerr << e.what() << std::endl;
		}
		ie1 = ib1 + ic1;
		
		textboxes["TEXTBOX_2_O2_IB"]->setText(handleinput.toString(ib1));
		textboxes["TEXTBOX_2_O2_IC"]->setText(handleinput.toString(ic1));
		textboxes["TEXTBOX_2_O2_IE"]->setText(handleinput.toString(ie1));
		break;
		/******************************************************************************************************/
	default:
		break;
	}

}

void Page2::endState()
{
	this->quit = true;
}

void Page2::initGUI()
{
	this->titlebar = new Titlebar(this->window, &this->font, "BJT level shift");
	this->footer = new Footer(this->window, &this->font);

	this->popups["POPUP_1"] = new gui::PopUp(&this->font, this->popup1text, 170.f, 150.f);
	this->popups["POPUP_2"] = new gui::PopUp(&this->font, this->popup2text, 740.f, 150.f);

	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);

	// SECTION 1  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image1"] = new gui::Image("Images/Page2Img1.png", 145.f, 85.f);

	this->buttons["BUTTON_CALC_1"] = new gui::Button(80.f, 545.f, "Calculate", &this->font);
	this->buttons["BUTTON_CALC_2"] = new gui::Button(300.f, 445.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_1"] = new gui::Button(180.f, 545.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_1_I1_VI"] = new gui::TextBox(80.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_VO"] = new gui::TextBox(80.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_IC1"] = new gui::TextBox(80.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_IC2"] = new gui::TextBox(80.f, 440.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_VBE"] = new gui::TextBox(80.f, 465.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_VCE"] = new gui::TextBox(80.f, 490.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I1_HFE"] = new gui::TextBox(80.f, 515.f, &this->font, true);

	this->textboxes["TEXTBOX_1_O1_R1"] = new gui::TextBox(190.f, 365.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O1_R2"] = new gui::TextBox(190.f, 390.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O1_R3"] = new gui::TextBox(190.f, 415.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O1_V"] = new gui::TextBox(190.f, 440.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O1_IB1"] = new gui::TextBox(190.f, 465.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O1_IB2"] = new gui::TextBox(190.f, 490.f, &this->font, false);
	
	this->textboxes["TEXTBOX_1_I2_R1"] = new gui::TextBox(300.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I2_R2"] = new gui::TextBox(300.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_1_I2_R3"] = new gui::TextBox(300.f, 415.f, &this->font, true);

	this->textboxes["TEXTBOX_1_O2_IB1"] = new gui::TextBox(410.f, 365.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O2_IB2"] = new gui::TextBox(410.f, 390.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O2_IC1"] = new gui::TextBox(410.f, 415.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O2_IC2"] = new gui::TextBox(410.f, 440.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O2_IE1"] = new gui::TextBox(410.f, 465.f, &this->font, false);
	this->textboxes["TEXTBOX_1_O2_IE2"] = new gui::TextBox(410.f, 490.f, &this->font, false);

	this->labels["LABEL_1_I1_VI"] = new gui::Label(58.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_1_I1_VO"] = new gui::Label(56.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_1_I1_IC1"] = new gui::Label(56.f, 415.f, &this->font, "Ic1", 12, sf::Color::White);
	this->labels["LABEL_1_I1_IC2"] = new gui::Label(56.f, 440.f, &this->font, "Ic2", 12, sf::Color::White);
	this->labels["LABEL_1_I1_VBE"] = new gui::Label(56.f, 465.f, &this->font, "Vbe", 12, sf::Color::White);
	this->labels["LABEL_1_I1_VCE"] = new gui::Label(56.f, 490.f, &this->font, "Vce", 12, sf::Color::White);
	this->labels["LABEL_1_I1_HFE"] = new gui::Label(56.f, 515.f, &this->font, "Hfe", 12, sf::Color::White);

	this->labels["LABEL_1_O1_R1"] = new gui::Label(166.f, 365.f, &this->font, "R1<", 12, sf::Color::White);
	this->labels["LABEL_1_O1_R2"] = new gui::Label(168.f, 390.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_1_O1_R3"] = new gui::Label(168.f, 415.f, &this->font, "R3", 12, sf::Color::White);
	this->labels["LABEL_1_O1_V"] = new gui::Label(172.f, 440.f, &this->font, "V", 12, sf::Color::White);
	this->labels["LABEL_1_O1_IB1"] = new gui::Label(166.f, 465.f, &this->font, "ib1>", 12, sf::Color::White);
	this->labels["LABEL_1_O1_IB2"] = new gui::Label(166.f, 490.f, &this->font, "ib2>", 12, sf::Color::White);

	this->labels["LABEL_1_I2_R1"] = new gui::Label(278.f, 365.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_1_I2_R2"] = new gui::Label(278.f, 390.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_1_I2_R3"] = new gui::Label(278.f, 415.f, &this->font, "R3", 12, sf::Color::White);

	this->labels["LABEL_1_O2_IB1"] = new gui::Label(388.f, 365.f, &this->font, "Ib1", 12, sf::Color::White);
	this->labels["LABEL_1_O2_IB2"] = new gui::Label(388.f, 390.f, &this->font, "Ib2", 12, sf::Color::White);
	this->labels["LABEL_1_O2_IC1"] = new gui::Label(388.f, 415.f, &this->font, "Ic1", 12, sf::Color::White);
	this->labels["LABEL_1_O2_IC2"] = new gui::Label(388.f, 440.f, &this->font, "Ic2", 12, sf::Color::White);
	this->labels["LABEL_1_O2_IE1"] = new gui::Label(388.f, 465.f, &this->font, "Ie1", 12, sf::Color::White);
	this->labels["LABEL_1_O2_IE2"] = new gui::Label(388.f, 490.f, &this->font, "Ie2", 12, sf::Color::White);
	
	// SECTION 2  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image2"] = new gui::Image("Images/Page2Img2.png", 710.f, 85.f);

	this->buttons["BUTTON_CALC_3"] = new gui::Button(630.f, 520.f, "Calculate", &this->font);
	this->buttons["BUTTON_CALC_4"] = new gui::Button(850.f, 420.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_2"] = new gui::Button(730.f, 520.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_2_I1_VI"] = new gui::TextBox(630.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I1_VO"] = new gui::TextBox(630.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I1_IC"] = new gui::TextBox(630.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I1_VBE"] = new gui::TextBox(630.f, 440.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I1_VCE"] = new gui::TextBox(630.f, 465.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I1_HFE"] = new gui::TextBox(630.f, 490.f, &this->font, true);

	this->textboxes["TEXTBOX_2_O1_R1"] = new gui::TextBox(740.f, 365.f, &this->font, false);
	this->textboxes["TEXTBOX_2_O1_R2"] = new gui::TextBox(740.f, 390.f, &this->font, false);
	this->textboxes["TEXTBOX_2_O1_V"] = new gui::TextBox(740.f, 415.f, &this->font, false);
	this->textboxes["TEXTBOX_2_O1_IB"] = new gui::TextBox(740.f, 440.f, &this->font, false);

	this->textboxes["TEXTBOX_2_I2_R1"] = new gui::TextBox(850.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_2_I2_R2"] = new gui::TextBox(850.f, 390.f, &this->font, true);

	this->textboxes["TEXTBOX_2_O2_IB"] = new gui::TextBox(960.f, 365.f, &this->font, false);
	this->textboxes["TEXTBOX_2_O2_IC"] = new gui::TextBox(960.f, 390.f, &this->font, false);
	this->textboxes["TEXTBOX_2_O2_IE"] = new gui::TextBox(960.f, 415.f, &this->font, false);

	this->labels["LABEL_2_I1_VI"] = new gui::Label(608.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_2_I1_VO"] = new gui::Label(608.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_2_I1_IC"] = new gui::Label(608.f, 415.f, &this->font, "Ic", 12, sf::Color::White);
	this->labels["LABEL_2_I1_VBE"] = new gui::Label(608.f, 440.f, &this->font, "Vbe", 12, sf::Color::White);
	this->labels["LABEL_2_I1_VCE"] = new gui::Label(608.f, 465.f, &this->font, "Vce", 12, sf::Color::White);
	this->labels["LABEL_2_I1_HFE"] = new gui::Label(608.f, 490.f, &this->font, "Hfe", 12, sf::Color::White);

	this->labels["LABEL_2_O1_R1"] = new gui::Label(718.f, 365.f, &this->font, "R1<", 12, sf::Color::White);
	this->labels["LABEL_2_O1_R2"] = new gui::Label(718.f, 390.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_2_O1_V"] = new gui::Label(718.f, 415.f, &this->font, "V", 12, sf::Color::White);
	this->labels["LABEL_2_O1_IB"] = new gui::Label(718.f, 440.f, &this->font, "Ib>", 12, sf::Color::White);

	this->labels["LABEL_2_I2_R1"] = new gui::Label(828.f, 365.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_2_I2_R2"] = new gui::Label(828.f, 390.f, &this->font, "R2", 12, sf::Color::White);

	this->labels["LABEL_2_O2_IB"] = new gui::Label(938.f, 365.f, &this->font, "Ib", 12, sf::Color::White);
	this->labels["LABEL_2_O2_IC"] = new gui::Label(938.f, 390.f, &this->font, "Ic", 12, sf::Color::White);
	this->labels["LABEL_2_O2_IE"] = new gui::Label(938.f, 415.f, &this->font, "Ie", 12, sf::Color::White);
}

void Page2::updateGUI()
{
	this->titlebar->update(this->mousePositionView, this->window);

	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->update(this->mousePositionView);

	for (auto &i : this->popups)
		i.second->update(this->mousePositionView);

	if (buttons["BUTTON_BACK"]->isReleased())
		this->pages->push_front(new PageMainMenu(this->window, ev, pages));

	if (buttons["BUTTON_CALC_1"]->isReleased())
		this->calculate(this->CALC_STATE_1);

	if (buttons["BUTTON_CALC_2"]->isReleased())
		this->calculate(this->CALC_STATE_2);

	if (buttons["BUTTON_CALC_3"]->isReleased())
		this->calculate(this->CALC_STATE_3);

	if (buttons["BUTTON_CALC_4"]->isReleased())
		this->calculate(this->CALC_STATE_4);

	if (buttons["BUTTON_HELP_1"]->isReleased())
		this->popups["POPUP_1"]->setVisibility(!this->popups["POPUP_1"]->getVisibility());

	if (buttons["BUTTON_HELP_2"]->isReleased())
		this->popups["POPUP_2"]->setVisibility(!this->popups["POPUP_2"]->getVisibility());
}

void Page2::updateInput()
{
	for (auto &i : this->textboxes)
		i.second->updateText(this->ev);
	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void Page2::updateMouseMov()
{
	this->titlebar->updateWindowPosition(this->window);
}


void Page2::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void Page2::renderGUI(sf::RenderTarget * target)
{
	this->titlebar->render(target);
	this->footer->render(target);

	for (auto &i : this->textboxes)
		i.second->render(target);

	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->labels)
		i.second->render(target);

	for (auto &i : this->images)
		i.second->render(target);

	for (auto &i : this->popups)
	{
		if (i.second->getVisibility())
			i.second->render(target);
	}
}

void Page2::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
