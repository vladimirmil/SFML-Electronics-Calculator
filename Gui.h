#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

namespace gui
{
	class Button
	{
	private:
		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;
		sf::Color idleColor, hoverColor, pressedColor, outlineColor;
		sf::Texture textureIdle, textureHover, texturePressed;
		float outlineThickness, isButtonReleased;
		bool isImage;
		short unsigned buttonState;

		enum button_state {
			BUTTON_IDLE = 0,
			BUTTON_HOVER,
			BUTTON_PRESSED,
			BUTTON_RELEASED,
		};

		void initVariables(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		void initShape(float x, float y, float width, float height);
		void initText(sf::Font* font, std::string text);
		void initTexture(std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);

	public:
		Button(float x, float y, std::string text, sf::Font* font);
		Button(float x, float y, float width, float height, std::string text, sf::Font* font);
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor,
			sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		Button(float x, float y, std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);
		virtual ~Button();

		const bool isPressed();
		const bool isReleased();
		int getButtonState();
		void updateEvent(sf::Event* ev, sf::Vector2f mousePosition);
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};

	class Label
	{
	private:
		sf::Font* font;
		sf::Text text;
	public:
		Label(float x, float y, sf::Font * font, std::string text, int size, sf::Color color);
		virtual ~Label();

		void render(sf::RenderTarget* target);
	};

	class TextBox
	{
	private:
		sf::RectangleShape shape, cursor;
		sf::Font* font;
		sf::Text text;

		std::string s;
		float width, height;
		bool isSelected, isInput;
		short unsigned textboxState;
		const int TEXT_OFFSET_X = 5;
		const int TEXT_OFFSET_Y = 8;
		const int BACKSPACE_KEY = 8;
		const int ENTER_KEY = 9;
		const int TAB_KEY = 13;

		enum textbox_state {
			TEXTBOX_IDLE,
			TEXTBOX_HOVER,
			TEXTBOX_PRESSED,
		};

		void initCursor();
		void initVariables();
		void initShape(float x, float y);
		void initText(sf::Font * font);

	public:
		TextBox(float x, float y, sf::Font * font, bool isInput);
		TextBox(float x, float y, float width, sf::Font * font, bool isInput);
		virtual ~TextBox();

		const bool getPressed() const;
		const bool getSelected() const;
		std::string getText();
		void setText(std::string text);
		void updateCursor();
		void updateText(sf::Event* ev);
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};

	class Image {
	private:
		sf::RectangleShape shape;
		sf::Texture texture;
		void initTexture(std::string textureLocation);
	public:
		Image(std::string textureLocation, float x, float y);
		Image(std::string textureLocation, float x, float y, float width, float height);
		virtual ~Image();

		void render(sf::RenderTarget* target);
	};

	class Graph {
	private:
		sf::RectangleShape background, background2;
		sf::Font* font;
		sf::VertexArray lines;
		sf::Color lineColor;
		std::vector<sf::Text*> text;
		std::vector<sf::CircleShape*> points;
		std::vector<sf::Vector2f> pointsPositions;
		std::vector<float> inputVectorX, inputVectorY;		
		int numberOfPoints;
		float spacing, margin, minY, maxY, minX, maxX, x, y, width, height;

		void initVariables(float x, float y, float height, float width, float margin, std::vector<float> inputVectorX, std::vector<float> inputVectorY);
		void initBackground(sf::Color color, sf::Color color2);
		void initText(sf::Font * font, std::string text);
		void initGraph();
	public:
		Graph(sf::Font* font, std::string title, std::vector<float> inputVectorX, std::vector<float> inputVectorY, float x, float y, float width, float height, float margin);
		virtual ~Graph();

		void setColor(sf::Color color);
		void clearGraph();
		void update(std::vector<float> inputVectorX, std::vector<float> inputVectorY, std::string title);
		void render(sf::RenderTarget* target);
	};

	class PopUp {
	private:
		sf::RectangleShape shape, button_shape;
		sf::Font* font;
		sf::Text text, button_text;
		bool visibility;
	public:
		PopUp(sf::Font* font, std::string text, float x, float y);
		virtual ~PopUp();

		bool getVisibility();
		void setVisibility(bool value);
		void update(sf::Vector2f mousePosition);
		void render(sf::RenderTarget* target);
	};
}

#endif // !GUI_H
