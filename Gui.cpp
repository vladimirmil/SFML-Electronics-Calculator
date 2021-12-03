#include "Gui.h"

/**************************************************************************
********* BUTTON **********************************************************
**************************************************************************/

void gui::Button::initVariables(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->isImage = false;
	this->buttonState = this->BUTTON_IDLE;
	this->outlineColor = outlineColor;
	this->outlineThickness = outlineThickness;
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->pressedColor = pressedColor;
}

void gui::Button::initShape(float x, float y, float width, float height)
{
	//this->isImage = false;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineColor(this->outlineColor);
	this->shape.setOutlineThickness(this->outlineThickness);
}

void gui::Button::initText(sf::Font * font, std::string text)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(14);
	this->text.setPosition(
		(int)this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		(int)this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 3
	);
}

void gui::Button::initTexture(std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed)
{
	if (!this->textureIdle.loadFromFile(textureLocationIdle))
	{
		throw("ERROR: Coudld not load image");
	}

	if (!this->textureHover.loadFromFile(textureLocationHover))
	{
		throw("ERROR: Coudld not load image");
	}

	if (!this->texturePressed.loadFromFile(textureLocationPressed))
	{
		throw("ERROR: Coudld not load image");
	}
}

gui::Button::Button(float x, float y, std::string text, sf::Font * font)
{
	this->isImage = false;
	this->buttonState = this->BUTTON_IDLE;
	this->outlineColor = sf::Color::Color(40, 40, 40, 255);
	this->outlineThickness = 1;
	this->idleColor = sf::Color::Color(45,45,45,255);
	this->hoverColor = sf::Color::Color(50, 50, 50, 255);
	this->pressedColor = sf::Color::Color(55, 55, 55, 255);

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(80, 25));
	this->shape.setFillColor(this->idleColor);
	this->shape.setOutlineColor(this->outlineColor);
	this->shape.setOutlineThickness(this->outlineThickness);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(14);
	this->text.setPosition(
		this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - 3
	);
}

gui::Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness)
{
	this->isImage = false;
	this->initVariables(idleColor, hoverColor, pressedColor, outlineColor, outlineThickness);
	this->initShape(x, y, width, height);
	this->initText(font, text);
}

gui::Button::Button(float x, float y, std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed)
{
	this->isImage = true;
	this->initTexture(textureLocationIdle, textureLocationHover, textureLocationPressed);
	this->buttonState = this->BUTTON_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(&this->textureIdle);
	this->shape.setSize(sf::Vector2f((float)this->textureIdle.getSize().x, (float)this->textureIdle.getSize().y));
	this->shape.setOutlineColor(sf::Color::Color(40,40,40,255));
	this->shape.setOutlineThickness(3);
}

gui::Button::~Button()
{
}

const bool gui::Button::isPressed()
{
	if (this->buttonState == this->BUTTON_PRESSED)
		return true;
	return false;
}

void gui::Button::update(sf::Vector2f mousePosition)
{
	
	this->buttonState = this->BUTTON_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = this->BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = this->BUTTON_PRESSED;
	}

	switch (buttonState)
	{
	case this->BUTTON_IDLE:
		if (!this->isImage)
			this->shape.setFillColor(this->idleColor);
		else
			this->shape.setTexture(&this->textureIdle);
		break;
	case this->BUTTON_HOVER:
		if (!this->isImage)
			this->shape.setFillColor(this->hoverColor);
		else
			this->shape.setTexture(&this->textureHover);
		break;
	case this->BUTTON_PRESSED:
		if (!this->isImage)
			this->shape.setFillColor(this->pressedColor);
		else
			this->shape.setTexture(&this->texturePressed);
		break;
	default:
		this->shape.setFillColor(this->idleColor);
		break;
	}
}

void gui::Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

/**************************************************************************
********* LABEL ***********************************************************
**************************************************************************/

gui::Label::Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setFillColor(color);
	this->text.setPosition(x, y);
}

gui::Label::~Label()
{
}

void gui::Label::render(sf::RenderTarget * target)
{
	target->draw(this->text);
}

/**************************************************************************
********* TEXTBOX *********************************************************
**************************************************************************/


void gui::TextBox::initCursor()
{
	this->cursor.setPosition(sf::Vector2f(this->text.getGlobalBounds().width + this->shape.getPosition().x + 5, this->shape.getPosition().y + 1));
	this->cursor.setSize(sf::Vector2f(1.f, this->height - 2));
	this->cursor.setFillColor(sf::Color::White);
}

void gui::TextBox::initVariables()
{
	this->textboxState = this->TEXTBOX_IDLE;
	this->isSelected = false;
	this->width = 80;
	this->height = 20;
}

void gui::TextBox::initShape(float x, float y)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(this->width, this->height));
	this->shape.setFillColor(sf::Color(51, 51, 51, 255));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color::Color(34, 30, 31, 255));
}

void gui::TextBox::initText(sf::Font * font)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString("");
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::White);
	this->text.setPosition(
		this->shape.getPosition().x + this->TEXT_OFFSET_X,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f - this->TEXT_OFFSET_Y
	);
}

gui::TextBox::TextBox(float x, float y, sf::Font * font, bool isInput)
{
	this->isInput = isInput;
	this->initVariables();
	this->initShape(x, y);
	this->initText(font);
	this->initCursor();
}

gui::TextBox::TextBox(float x, float y, float width, sf::Font * font, bool isInput)
{
	this->isInput = isInput;
	this->initVariables();
	this->width = width;
	this->initShape(x, y);
	this->initText(font);
	this->initCursor();
}

gui::TextBox::~TextBox()
{
}

const bool gui::TextBox::getPressed() const
{
	if (this->textboxState == this->TEXTBOX_PRESSED)
		return true;
	return false;
}

const bool gui::TextBox::getSelected() const
{
	return this->isSelected;
}

std::string gui::TextBox::getText()
{
	return this->text.getString();
}

void gui::TextBox::setText(std::string text)
{
	this->text.setString(text);
}

void gui::TextBox::updateCursor()
{
	this->cursor.setPosition(sf::Vector2f(this->text.getGlobalBounds().width + this->shape.getPosition().x + 5, this->shape.getPosition().y + 1));
}

void gui::TextBox::updateText(sf::Event* ev)
{
	if (this->isInput)
	{
		if (this->getSelected() && ev->text.unicode < 128 && ev->text.unicode > 2 && text.getGlobalBounds().width < /*this->MAX_TEXT_LENGHT*/this->width - 12 && ev->text.unicode != this->BACKSPACE_KEY
			&& ev->text.unicode != this->ENTER_KEY && ev->text.unicode != this->TAB_KEY)
		{
			this->s += static_cast<char>(ev->text.unicode);
		}
		else if (this->getSelected() && ev->text.unicode == this->BACKSPACE_KEY && s.size() != 0)
		{
			s.pop_back();
		}

		this->text.setString(this->s);
	}
	
}

void gui::TextBox::update(sf::Vector2f mousePosition)
{
	if (this->getSelected())
	{
		this->updateCursor();
		this->shape.setOutlineThickness(2);
		this->shape.setOutlineColor(sf::Color::Color(0, 93, 233, 255));	//blue
		//this->shape.setOutlineColor(sf::Color::Color(250, 175, 0, 255));		//yellow/gold
	}
	else
	{
		this->shape.setOutlineThickness(1);
		this->shape.setOutlineColor(sf::Color::Color(34, 30, 31, 255));
	}

	this->textboxState = this->TEXTBOX_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		this->textboxState = this->TEXTBOX_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = this->TEXTBOX_PRESSED;
			this->isSelected = true;
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->textboxState = this->TEXTBOX_IDLE;
			this->isSelected = false;
		}
	}
}

void gui::TextBox::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);

	if (getSelected())
		target->draw(this->cursor);
}


/**************************************************************************
********* IMAGE **********************************************************
**************************************************************************/

void gui::Image::initTexture(std::string textureLocation)
{
	if (!this->texture.loadFromFile(textureLocation))
	{
		throw("ERROR: Coudld not load image");
	}
}

gui::Image::Image(std::string textureLocation, float x, float y)
{
	this->initTexture(textureLocation);
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setTexture(&this->texture);
	this->shape.setSize(sf::Vector2f((float)this->texture.getSize().x, (float)this->texture.getSize().y));
}

gui::Image::Image(std::string textureLocation, float x, float y, float width, float height)
{
	this->initTexture(textureLocation);
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setTexture(&this->texture);
}

gui::Image::~Image()
{
}

void gui::Image::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

/**************************************************************************
********* GRAPH ***********************************************************
**************************************************************************/

void gui::Graph::initVariables(float x, float y, float height, float width, float margin, std::vector<float> inputVectorX, std::vector<float> inputVectorY)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
	this->margin = margin;
	this->inputVectorX = inputVectorX;
	this->inputVectorY = inputVectorY;
}


void gui::Graph::initBackground(sf::Color color1, sf::Color color2)
{
	this->background.setSize(sf::Vector2f(this->width, this->height));
	this->background.setOutlineThickness(1);
	this->background.setOutlineColor(sf::Color(42, 42, 42, 255));
	this->background.setFillColor(color1);
	this->background.setPosition(sf::Vector2f(this->x, this->y));

	this->background2.setSize(sf::Vector2f(this->width - 2 * this->margin, this->height - 2 * this->margin));
	this->background2.setFillColor(color2);
	this->background.setOutlineThickness(2);
	this->background.setOutlineColor(sf::Color(46, 46, 46, 255));
	this->background2.setPosition(sf::Vector2f(this->x + this->margin, this->y + this->margin));
}

void gui::Graph::initText(sf::Font * font, std::string text)
{
	this->font = font;
	for (unsigned int i = 0; i < 5; i++)
	{
		this->text.push_back(new sf::Text);
		this->text[i]->setFont(*this->font);
		this->text[i]->setFillColor(sf::Color::White);
		this->text[i]->setCharacterSize(10);
	}
	this->text[0]->setString(text);
	this->text[0]->setPosition(
		this->background.getPosition().x + (int)(this->background.getGlobalBounds().width / 2) - (int)this->text[0]->getGlobalBounds().width / 2 - 3,
		this->background.getPosition().y + (this->margin / 4)
	);
	
	this->text[1]->setString(std::to_string((int)this->minX));
	this->text[1]->setPosition(
		this->background.getPosition().x + this->margin,
		this->background.getPosition().y + this->background.getGlobalBounds().height - (int)(4 * this->margin / 5)
	);
	this->text[2]->setString(std::to_string((int)this->maxX));
	this->text[2]->setPosition(
		this->background.getPosition().x + this->background.getGlobalBounds().width - this->margin - (int)this->text[2]->getLocalBounds().width,
		this->background.getPosition().y + this->background.getGlobalBounds().height - (int)(4 * this->margin / 5)
	);
	this->text[3]->setString(std::to_string((int)this->minY));
	this->text[3]->setPosition(
		this->background.getPosition().x,
		this->background.getPosition().y + this->background.getGlobalBounds().height - this->margin - (int)(6 * this->text[2]->getLocalBounds().height / 4)
	);
	this->text[4]->setString(std::to_string((int)this->maxY));
	this->text[4]->setPosition(
		this->background.getPosition().x,
		this->background.getPosition().y + this->margin
	);
}

void gui::Graph::initGraph()
{
	if (this->inputVectorX.size() == this->inputVectorY.size() && this->inputVectorX.size() != 0)
	{
		this->numberOfPoints = this->inputVectorX.size();
		//this->spacing = (width - 2 * this->margin) / (this->numberOfPoints - 1);
		//find min and max of input vectors
		const auto minmaxX = std::minmax_element(this->inputVectorX.begin(), this->inputVectorX.end());
		const auto minmaxY = std::minmax_element(this->inputVectorY.begin(), this->inputVectorY.end());
		this->minX = *minmaxX.first;
		this->maxX = *minmaxX.second;
		this->minY = *minmaxY.first;
		this->maxY = *minmaxY.second;
		//init lines 
		this->lines = sf::VertexArray(sf::LineStrip, this->numberOfPoints);

		for (int i = 0; i < this->numberOfPoints; i++)
		{
			//add new point
			this->points.push_back(new sf::CircleShape);
			//populate vector
			this->pointsPositions.push_back(sf::Vector2f(0, 0));
			//normalize input vectors 0-100
			this->inputVectorY[i] = ((this->inputVectorY[i] - this->minY) / (this->maxY - this->minY)) * 100;
			this->inputVectorX[i] = ((this->inputVectorX[i] - this->minX) / (this->maxX - this->minX)) * 100;
			//scale values. 100 being the maximum. top left is 0,0 so 1-(...) at Y to invert it
			this->pointsPositions[i].y = ((1 - (this->inputVectorY[i] / 100))) * (this->height - 2 * this->margin) + this->y + this->margin;
			this->pointsPositions[i].x = (this->inputVectorX[i] / 100) * (this->width - 2 * this->margin) + this->x + this->margin;

			this->points[i]->setPosition(sf::Vector2f(this->pointsPositions[i].x, this->pointsPositions[i].y));
			this->points[i]->setRadius(3);
			this->points[i]->setFillColor(sf::Color::Red);
			this->points[i]->setPointCount(50);
			this->lines[i].color = sf::Color::Red;
			this->lines[i].position = sf::Vector2f(this->pointsPositions[i].x + 2.f, this->pointsPositions[i].y + 2.f);
		}
	}
}

gui::Graph::Graph(sf::Font * font, std::string title, std::vector<float> inputVectorX, std::vector<float> inputVectorY, float x, float y,
				float width, float height, float margin)
{
	this->initVariables(x, y, height, width, margin, inputVectorX, inputVectorY);
	this->initBackground(sf::Color(45, 45, 45, 255), sf::Color(48, 48, 48, 255));
	this->initGraph();
	this->initText(font, title);
}

gui::Graph::~Graph()
{
	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		std::cout << "Delete: Point" << std::endl;
		delete points[i];
	}

	for (unsigned int i = 0; i < this->text.size(); i++)
	{
		std::cout << "Delete: Text" << std::endl;
		delete text[i];
	}
}

void gui::Graph::clearGraph()
{
	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		std::cout << "Delete: Point" << std::endl;
		delete points[i];
	}
	lines.clear();
	this->points.clear();
	this->pointsPositions.clear();
	this->inputVectorX.clear();
	this->inputVectorY.clear();
}

void gui::Graph::update(std::vector<float> inputVectorX, std::vector<float> inputVectorY, std::string title)
{
	this->clearGraph();
	this->inputVectorX = inputVectorX;
	this->inputVectorY = inputVectorY;

	if (this->inputVectorX.size() == this->inputVectorY.size() && this->inputVectorX.size() != 0)
	{
		this->text[0]->setString(title);
		this->numberOfPoints = this->inputVectorX.size();
		const auto minmaxX = std::minmax_element(this->inputVectorX.begin(), this->inputVectorX.end());
		const auto minmaxY = std::minmax_element(this->inputVectorY.begin(), this->inputVectorY.end());
		this->minX = *minmaxX.first;
		this->maxX = *minmaxX.second;
		this->minY = *minmaxY.first;
		this->maxY = *minmaxY.second;

		this->text[1]->setString(std::to_string((int)this->minX));
		this->text[2]->setString(std::to_string((int)this->maxX));
		this->text[3]->setString(std::to_string((int)this->minY));
		this->text[4]->setString(std::to_string((int)this->maxY));

		this->lines = sf::VertexArray(sf::LineStrip, this->numberOfPoints);

		for (int i = 0; i < this->numberOfPoints; i++)
		{
			//add new point
			this->points.push_back(new sf::CircleShape);
			//populate vector
			this->pointsPositions.push_back(sf::Vector2f(0, 0));
			//normalize input vectors 0-100
			this->inputVectorY[i] = ((this->inputVectorY[i] - this->minY) / (this->maxY - this->minY)) * 100;
			this->inputVectorX[i] = ((this->inputVectorX[i] - this->minX) / (this->maxX - this->minX)) * 100;
			//scale values. 100 being the maximum. top left is 0,0 so 1-(...) at Y to invert it
			this->pointsPositions[i].y = ((1 - (this->inputVectorY[i] / 100))) * (this->height - 2 * margin) + this->y + margin;
			this->pointsPositions[i].x = (this->inputVectorX[i] / 100) * (this->width - 2 * margin) + this->x + margin;

			this->points[i]->setPosition(sf::Vector2f(this->pointsPositions[i].x, this->pointsPositions[i].y));
			this->points[i]->setRadius(3);
			this->points[i]->setFillColor(sf::Color::Red);
			this->points[i]->setPointCount(50);
			this->lines[i].color = sf::Color::Red;
			this->lines[i].position = sf::Vector2f(this->pointsPositions[i].x + 2.f, this->pointsPositions[i].y + 2.f);
		}
	}
	else
		this->text[0]->setString("ERROR: X,Y size mismatch or no input was given");
		
}

void gui::Graph::render(sf::RenderTarget * target)
{
	target->draw(this->background);
	target->draw(this->background2);
		
	for (int i = 0; i < 5; i++)
	{
		target->draw(*this->text[i]);
	}

	for (unsigned int i = 0; i < this->points.size(); i++)
	{
		target->draw(*this->points[i]);
		target->draw(lines);
	}
	
}
