#include "Page1.h"

void Page1::initBackground(sf::RenderWindow* window)
{
	this->background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	this->background.setFillColor(sf::Color(37, 37, 37, 255));
}

void Page1::initPopUpText()
{
	this->popup1text.append("Non-inv op-amp with non-inv reference\n\n");
	this->popup1text.append("This circuit can be used to translate\na sensor output voltage with a positive\n");
	this->popup1text.append("slope and negative offset to a usable\nADC input voltage range.\n\n");
	this->popup1text.append("Valid prefixes: G, M, K, m, u, n, p");

	this->popup2text.append("   Non-inv op-amp with inv reference\n\n");						
	this->popup2text.append("This circuit can be used to translate\na sensor output voltage with a positive\n");
	this->popup2text.append("slope and positive offset to a usable\nADC input voltage range.\n\n");
	this->popup2text.append("Valid prefixes: G, M, K, m, u, n, p");
		
	this->popup3text.append("   Inv op-amp with non-inv reference\n\n");
	this->popup3text.append("This circuit can be used to translate\na sensor output voltage with a positive\n");
	this->popup3text.append("slope and negative offset to a usable\nADC input voltage range.\n\n");
	this->popup3text.append("Valid prefixes: G, M, K, m, u, n, p");
	
	this->popup4text.append("      Inv op-amp with inv reference\n\n");
	this->popup4text.append("This circuit can be used to translate\na negative sensor output voltage to a\n");
	this->popup4text.append("usable ADC input voltage range.\n\n\n");
	this->popup4text.append("Valid prefixes: G, M, K, m, u, n, p");
}

Page1::Page1(sf::RenderWindow* window, sf::Event* ev, std::deque<Page*>* pages) : Page(window, ev, pages)
{
	if (!this->pages->empty())
		this->pages->back()->endState();

	this->calculateState = this->CALC_STATE_0;
	this->initPopUpText();
	this->initBackground(window);
	this->initGUI();
}

Page1::~Page1()
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
}

void Page1::calculate(calculate_state calculateState)
{
	double r1, r2, r3, r4, vimin, vimax, vomin, vomax, vr, gain = 0;

	switch (calculateState)
	{
	case this->CALC_STATE_1:

		vimin = handleinput.getDouble(this->textboxes["TEXTBOX_1_VIMIN"]->getText());
		vimax = handleinput.getDouble(this->textboxes["TEXTBOX_1_VIMAX"]->getText());
		vomin = handleinput.getDouble(this->textboxes["TEXTBOX_1_VOMIN"]->getText());
		vomax = handleinput.getDouble(this->textboxes["TEXTBOX_1_VOMAX"]->getText());
		vr = handleinput.getDouble(this->textboxes["TEXTBOX_1_VR"]->getText());
		
		r1 = 1000;
		r4 = 1000;

		// gain = (vomax - vomin) / (vimax - vimin)
		try { gain = handleinput.divisionException((vomax - vomin), (vimax - vimin)); }
		catch (std::invalid_argument &e) 
		{
			gain = -1;
			std::cerr << e.what() << std::endl;
		}
		if (gain < 1)
		{
			r2 = 0;
			r3 = 0;
		}
		else
		{
			// r2 = (-1000 * vr) / (vimin * gain + vr - vr * gain - vomin)
			try { r2 = handleinput.divisionException((-1000 * vr), (vimin * gain + vr - vr * gain - vomin)); }
			catch (std::invalid_argument &e) 
			{
				r2 = -1;
				std::cerr << e.what() << std::endl;
			}
			// r3 = ((1000000 + (1000 * r2)) / (gain * r2)) - 1000;
			try { r3 = handleinput.divisionException((1000000 + (1000 * r2)), (gain * r2));  r3 = r3 - 1000; }
			catch (std::invalid_argument &e) 
			{
				r3 = -1;
				std::cerr << e.what() << std::endl;
			}
		}
		textboxes["TEXTBOX_1_R1"]->setText(handleinput.toString(r1));
		textboxes["TEXTBOX_1_R2"]->setText(handleinput.toString(r2));
		textboxes["TEXTBOX_1_R3"]->setText(handleinput.toString(r3));
		textboxes["TEXTBOX_1_R4"]->setText(handleinput.toString(r4));
		break;

	case this->CALC_STATE_2:

		vimin = handleinput.getDouble(this->textboxes["TEXTBOX_2_VIMIN"]->getText());
		vimax = handleinput.getDouble(this->textboxes["TEXTBOX_2_VIMAX"]->getText());
		vomin = handleinput.getDouble(this->textboxes["TEXTBOX_2_VOMIN"]->getText());
		vomax = handleinput.getDouble(this->textboxes["TEXTBOX_2_VOMAX"]->getText());
		vr = handleinput.getDouble(this->textboxes["TEXTBOX_2_VR"]->getText());

		r1 = 1000;
		r4 = 1000;
		// gain = (vomax - vomin) / (vimax - vimin)
		try { gain = handleinput.divisionException((vomax - vomin), (vimax - vimin)); }
		catch (std::invalid_argument &e) 
		{
			gain = -1;
			std::cerr << e.what() << std::endl;
		}
		if (gain <= 1)
		{
			r2 = -1;
			r3 = -1;
		}		
		else
		{
			// r2 = (-vr * 1000) / (vomin - (vimin * gain))
			try { r2 = handleinput.divisionException((-vr * 1000), (vomin - (vimin * gain))); }
			catch (std::invalid_argument &e) 
			{
				r2 = -1;
				std::cerr << e.what() << std::endl;
			}
			// r3 = ( (1000000 + (1000 * r2)) / (gain * r2) ) - 1000
			try { r3 = handleinput.divisionException((1000000 + (1000 * r2)), (gain * r2));  r3 = r3 - 1000; }
			catch (std::invalid_argument &e) 
			{
				r3 = -1;
				std::cerr << e.what() << std::endl;
			}
		}

		textboxes["TEXTBOX_2_R1"]->setText(handleinput.toString(r1));
		textboxes["TEXTBOX_2_R2"]->setText(handleinput.toString(r2));
		textboxes["TEXTBOX_2_R3"]->setText(handleinput.toString(r3));
		textboxes["TEXTBOX_2_R4"]->setText(handleinput.toString(r4));
		break;

	case this->CALC_STATE_3:


		vimin = handleinput.getDouble(this->textboxes["TEXTBOX_3_VIMIN"]->getText());
		vimax = handleinput.getDouble(this->textboxes["TEXTBOX_3_VIMAX"]->getText());
		vomin = handleinput.getDouble(this->textboxes["TEXTBOX_3_VOMIN"]->getText());
		vomax = handleinput.getDouble(this->textboxes["TEXTBOX_3_VOMAX"]->getText());
		r2 = handleinput.getDouble(this->textboxes["TEXTBOX_3_R2"]->getText());

		// gain = (vomax - vomin) / (vimax - vimin)
		try { gain = handleinput.divisionException((vomax - vomin), (vimax - vimin)); }
		catch (std::invalid_argument &e) 
		{
			gain = -1;
			std::cerr << e.what() << std::endl;
		}
		r1 = gain * r2;
		// r4 = k (temp var)
		try { r4 = handleinput.divisionException(r1, r2); }
		catch (std::invalid_argument &e)
		{
			r4 = -1;
			std::cerr << e.what() << std::endl;
		}
		// vr = ((vimax * k) + vomin) / (1 + k)
		try { vr = handleinput.divisionException(((vimax * r4) + vomin), (1 + r4)); }
		catch (std::invalid_argument &e) 
		{
			vr = -1;
			std::cerr << e.what() << std::endl;
		}

		textboxes["TEXTBOX_3_R1"]->setText(handleinput.toString(r1));
		textboxes["TEXTBOX_3_VR"]->setText(handleinput.toString(vr));
		break;

	case this->CALC_STATE_4:

		vimin = handleinput.getDouble(this->textboxes["TEXTBOX_4_VIMIN"]->getText());
		vimax = handleinput.getDouble(this->textboxes["TEXTBOX_4_VIMAX"]->getText());
		vomin = handleinput.getDouble(this->textboxes["TEXTBOX_4_VOMIN"]->getText());
		vomax = handleinput.getDouble(this->textboxes["TEXTBOX_4_VOMAX"]->getText());
		r1 = handleinput.getDouble(this->textboxes["TEXTBOX_4_R1"]->getText());
		vr = handleinput.getDouble(this->textboxes["TEXTBOX_4_VR"]->getText());

		// r4 = k (temp var)
		r4 = 0; 
		// gain = (vomax - vomin) / (vimax - vimin)
		try { gain = handleinput.divisionException((vomax - vomin), (vimax - vimin)); }
		catch (std::invalid_argument &e) 
		{
			gain = -1;
			std::cerr << e.what() << std::endl;
		}
		// r2 = r1 / gain
		try { r2 = handleinput.divisionException(r1, gain); }
		catch (std::invalid_argument &e) 
		{
			r2 = -1;
			std::cerr << e.what() << std::endl;
		}
		// k = (omin + imax * gain) / (-vref)
		try { r4 = handleinput.divisionException((vomin + vimax * gain), (-vr)); }
		catch (std::invalid_argument &e) 
		{
			r4 = -1;
			std::cerr << e.what() << std::endl;
		}
		// r3 = r1 / k
		try { r3 = handleinput.divisionException(r1, r4); }
		catch (std::invalid_argument &e) 
		{
			r3 = -1;
			std::cerr << e.what() << std::endl;
		}
		
		textboxes["TEXTBOX_4_R2"]->setText(handleinput.toString(r2));
		textboxes["TEXTBOX_4_R3"]->setText(handleinput.toString(r3));
		break;

	default:
		break;
	}
	
}

void Page1::endState()
{
	this->quit = true;
}

void Page1::initGUI()
{
	this->buttons["BUTTON_BACK"] = new gui::Button(22.f, 45.f, "Back", &this->font);

	this->popups["POPUP_1"] = new gui::PopUp(&this->font, this->popup1text, 20.f, 150.f);
	this->popups["POPUP_2"] = new gui::PopUp(&this->font, this->popup2text, 300.f, 150.f);
	this->popups["POPUP_3"] = new gui::PopUp(&this->font, this->popup3text, 580.f, 150.f);
	this->popups["POPUP_4"] = new gui::PopUp(&this->font, this->popup4text, 850.f, 150.f);

	// SECTION 1  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image1"] = new gui::Image("Images/Page1Img1.png", 22.5f, 85.f);

	this->buttons["BUTTON_CALC_1"] = new gui::Button(62.f, 470.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_1"] = new gui::Button(162.f, 470.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_1_VIMIN"] = new gui::TextBox(62.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_1_VIMAX"] = new gui::TextBox(151.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_1_VOMIN"] = new gui::TextBox(62.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_1_VOMAX"] = new gui::TextBox(151.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_1_VR"] = new gui::TextBox(62.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_1_R1"] = new gui::TextBox(62.f, 505.f, &this->font, false);
	this->textboxes["TEXTBOX_1_R2"] = new gui::TextBox(62.f, 530.f, &this->font, false);
	this->textboxes["TEXTBOX_1_R3"] = new gui::TextBox(62.f, 555.f, &this->font, false);
	this->textboxes["TEXTBOX_1_R4"] = new gui::TextBox(62.f, 580.f, &this->font, false);

	this->labels["LABEL_1_MIN"] = new gui::Label(88.f, 345.f, &this->font, "min", 12, sf::Color::White);
	this->labels["LABEL_1_MAX"] = new gui::Label(177.f, 345.f, &this->font, "max", 12, sf::Color::White);
	this->labels["LABEL_1_VI"] = new gui::Label(40.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_1_VO"] = new gui::Label(40.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_1_VR"] = new gui::Label(40.f, 415.f, &this->font, "Vr", 12, sf::Color::White);
	this->labels["LABEL_1_R1"] = new gui::Label(40.f, 505.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_1_R2"] = new gui::Label(40.f, 530.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_1_R3"] = new gui::Label(40.f, 555.f, &this->font, "R3", 12, sf::Color::White);
	this->labels["LABEL_1_R4"] = new gui::Label(40.f, 580.f, &this->font, "R4", 12, sf::Color::White);

	// SECTION 2  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image2"] = new gui::Image("Images/Page1Img2.png", 297.5f, 85.f);

	this->buttons["BUTTON_CALC_2"] = new gui::Button(325.f, 470.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_2"] = new gui::Button(425.f, 470.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_2_VIMIN"] = new gui::TextBox(325.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_2_VIMAX"] = new gui::TextBox(414.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_2_VOMIN"] = new gui::TextBox(325.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_2_VOMAX"] = new gui::TextBox(414.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_2_VR"] = new gui::TextBox(325.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_2_R1"] = new gui::TextBox(325.f, 505.f, &this->font, false);
	this->textboxes["TEXTBOX_2_R2"] = new gui::TextBox(325.f, 530.f, &this->font, false);
	this->textboxes["TEXTBOX_2_R3"] = new gui::TextBox(325.f, 555.f, &this->font, false);
	this->textboxes["TEXTBOX_2_R4"] = new gui::TextBox(325.f, 580.f, &this->font, false);

	this->labels["LABEL_2_MIN"] = new gui::Label(351.f, 345.f, &this->font, "min", 12, sf::Color::White);
	this->labels["LABEL_2_MAX"] = new gui::Label(440.f, 345.f, &this->font, "max", 12, sf::Color::White);
	this->labels["LABEL_2_VI"] = new gui::Label(303.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_2_VO"] = new gui::Label(303.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_2_VR"] = new gui::Label(303.f, 415.f, &this->font, "Vr", 12, sf::Color::White);
	this->labels["LABEL_2_R1"] = new gui::Label(303.f, 505.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_2_R2"] = new gui::Label(303.f, 530.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_2_R3"] = new gui::Label(303.f, 555.f, &this->font, "R3", 12, sf::Color::White);
	this->labels["LABEL_2_R4"] = new gui::Label(303.f, 580.f, &this->font, "R4", 12, sf::Color::White);

	// SECTION 3  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image3"] = new gui::Image("Images/Page1Img3.png", 572.5f, 85.f);

	this->buttons["BUTTON_CALC_3"] = new gui::Button(600.f, 470.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_3"] = new gui::Button(700.f, 470.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_3_VIMIN"] = new gui::TextBox(600.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_3_VIMAX"] = new gui::TextBox(692.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_3_VOMIN"] = new gui::TextBox(600.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_3_VOMAX"] = new gui::TextBox(692.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_3_R2"] = new gui::TextBox(600.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_3_VR"] = new gui::TextBox(600.f, 505.f, &this->font, false);
	this->textboxes["TEXTBOX_3_R1"] = new gui::TextBox(600.f, 530.f, &this->font, false);

	this->labels["LABEL_3_MIN"] = new gui::Label(626.f, 345.f, &this->font, "min", 12, sf::Color::White);
	this->labels["LABEL_3_MAX"] = new gui::Label(718.f, 345.f, &this->font, "max", 12, sf::Color::White);
	this->labels["LABEL_3_VI"] = new gui::Label(578.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_3_VO"] = new gui::Label(578.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_3_VR"] = new gui::Label(578.f, 505.f, &this->font, "Vr", 12, sf::Color::White);
	this->labels["LABEL_3_R1"] = new gui::Label(578.f, 530.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_3_R2"] = new gui::Label(578.f, 415.f, &this->font, "R2", 12, sf::Color::White);

	// SECTION 4  ////////////////////////////////////////////////////////////////////////////////////////////////
	this->images["Image4"] = new gui::Image("Images/Page1Img4.png", 847.5f, 85.f);

	this->buttons["BUTTON_CALC_4"] = new gui::Button(875.f, 470.f, "Calculate", &this->font);
	this->buttons["BUTTON_HELP_4"] = new gui::Button(975.f, 470.f, 25.f, 25.f, "?", &this->font);

	this->textboxes["TEXTBOX_4_VIMIN"] = new gui::TextBox(875.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_4_VIMAX"] = new gui::TextBox(965.f, 365.f, &this->font, true);
	this->textboxes["TEXTBOX_4_VOMIN"] = new gui::TextBox(875.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_4_VOMAX"] = new gui::TextBox(965.f, 390.f, &this->font, true);
	this->textboxes["TEXTBOX_4_VR"] = new gui::TextBox(875.f, 415.f, &this->font, true);
	this->textboxes["TEXTBOX_4_R1"] = new gui::TextBox(875.f, 440.f, &this->font, true);
	this->textboxes["TEXTBOX_4_R2"] = new gui::TextBox(875.f, 505.f, &this->font, false);
	this->textboxes["TEXTBOX_4_R3"] = new gui::TextBox(875.f, 530.f, &this->font, false);

	this->labels["LABEL_4_MIN"] = new gui::Label(901.f, 345.f, &this->font, "min", 12, sf::Color::White);
	this->labels["LABEL_4_MAX"] = new gui::Label(991.f, 345.f, &this->font, "max", 12, sf::Color::White);
	this->labels["LABEL_4_VI"] = new gui::Label(853.f, 365.f, &this->font, "Vi", 12, sf::Color::White);
	this->labels["LABEL_4_VO"] = new gui::Label(853.f, 390.f, &this->font, "Vo", 12, sf::Color::White);
	this->labels["LABEL_4_VR"] = new gui::Label(853.f, 415.f, &this->font, "Vr", 12, sf::Color::White);
	this->labels["LABEL_4_R1"] = new gui::Label(853.f, 440.f, &this->font, "R1", 12, sf::Color::White);
	this->labels["LABEL_4_R2"] = new gui::Label(853.f, 505.f, &this->font, "R2", 12, sf::Color::White);
	this->labels["LABEL_4_R3"] = new gui::Label(853.f, 530.f, &this->font, "R3", 12, sf::Color::White);

}

void Page1::updateGUI()
{
	for (auto &i : this->buttons)
		i.second->update(this->mousePositionView);

	for (auto &i : this->textboxes)
		i.second->update(this->mousePositionView);

	for (auto &i : this->popups)
		i.second->update(this->mousePositionView);

	if (buttons["BUTTON_BACK"]->isReleased())
		this->pages->push_front(new PageMain(this->window, ev, pages));

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

	if (buttons["BUTTON_HELP_3"]->isReleased())
		this->popups["POPUP_3"]->setVisibility(!this->popups["POPUP_3"]->getVisibility());

	if (buttons["BUTTON_HELP_4"]->isReleased())
		this->popups["POPUP_4"]->setVisibility(!this->popups["POPUP_4"]->getVisibility());
}

void Page1::updateInput()
{
	for (auto &i : this->textboxes)
		i.second->updateText(this->ev);

	for (auto &i : this->buttons)
		i.second->updateEvent(this->ev, this->mousePositionView);
}

void Page1::update()
{
	this->checkQuit();
	this->updateMousePositions();
	this->updateGUI();
}

void Page1::renderGUI(sf::RenderTarget * target)
{
	for (auto &i : this->buttons)
		i.second->render(target);

	for (auto &i : this->textboxes)
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

void Page1::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;
	target->clear();
	target->draw(this->background);
	this->renderGUI(target);
}
