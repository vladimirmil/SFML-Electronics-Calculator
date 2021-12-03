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
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color pressedColor;
		sf::Color outlineColor;
		sf::Texture textureIdle;
		sf::Texture textureHover;
		sf::Texture texturePressed;
		float outlineThickness;
		bool isImage;
		short unsigned buttonState;

		enum button_state {
			BUTTON_IDLE,
			BUTTON_HOVER,
			BUTTON_PRESSED,
		};

		void initVariables(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		void initShape(float x, float y, float width, float height);
		void initText(sf::Font* font, std::string text);
		void initTexture(std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);

	public:
		Button(float x, float y, std::string text, sf::Font* font);
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor,
			sf::Color pressedColor, sf::Color outlineColor, float outlineThickness);
		Button(float x, float y, std::string textureLocationIdle, std::string textureLocationHover, std::string textureLocationPressed);
		virtual ~Button();

		const bool isPressed();
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
		sf::RectangleShape shape;
		sf::RectangleShape cursor;
		sf::Font* font;
		sf::Text text;

		std::string s;
		float width;
		float height;
		bool isSelected;
		bool isInput;
		short unsigned textboxState;
		const int TEXT_OFFSET_X = 5;
		const int TEXT_OFFSET_Y = 8;
		const int MAX_TEXT_LENGHT = 68;
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
		sf::RectangleShape background;
		sf::RectangleShape background2;
		sf::Font* font;
		sf::VertexArray lines;
		std::vector<sf::Text*> text;
		std::vector<sf::CircleShape*> points;
		std::vector<sf::Vector2f> pointsPositions;
		std::vector<float> inputVectorX;
		std::vector<float> inputVectorY;
		
		int numberOfPoints;
		float spacing, margin, minY, maxY, minX, maxX, x, y, width, height;

		void initVariables(float x, float y, float height, float width, float margin, std::vector<float> inputVectorX, std::vector<float> inputVectorY);
		void initBackground(sf::Color color, sf::Color color2);
		void initText(sf::Font * font, std::string text);
		void initGraph();
	public:
		Graph(sf::Font* font, std::string title, std::vector<float> inputVectorX, std::vector<float> inputVectorY, float x, float y, float width, float height, float margin);
		virtual ~Graph();

		void clearGraph();
		void update(std::vector<float> inputVectorX, std::vector<float> inputVectorY, std::string title);
		void render(sf::RenderTarget* target);
	};
}

#endif // !GUI_H
