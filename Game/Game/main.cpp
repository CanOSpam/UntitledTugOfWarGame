#include "Precompiled.h"
#include "SFML/Graphics.hpp"

void RenderSquare(sf::RenderWindow& window, float x, float y);

int main()
{
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height/2), "Untitled Tug Of War Game", sf::Style::Default);

	float x = 0.0f;
	float y = 0.0f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::KeyPressed:
				break;

				// key pressed
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					x = event.mouseButton.x;
					y = event.mouseButton.y;
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}

		window.clear();

		RenderSquare(window, x, y);
		window.display();
	}

	return 0;
}

void RenderSquare(sf::RenderWindow& window, float x, float y)
{
	sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}