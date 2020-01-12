#include "Precompiled.h"
#include "SFML_Renderer.h"

SFML_Renderer::SFML_Renderer(std::shared_ptr<std::vector<Unit>> unit_list_ptr, std::shared_ptr<sf::RenderWindow> SFML_window)
	: m_unit_list_ptr(std::move(unit_list_ptr))
	, m_SFML_window(std::move(SFML_window))
{
}

void SFML_Renderer::render()
{
	m_SFML_window->clear();
	_render_background();
	_render_objects();
	_render_text();
	m_SFML_window->display();
}

void SFML_Renderer::_render_background()
{
}

void SFML_Renderer::_render_objects()
{
	for (auto&& unit : *m_unit_list_ptr)
	{
		sf::Color unit_colour;
		float unit_x;
		float unit_y;

		const unsigned int THIRD_OF_SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height / 2 / 3;

		if (unit.m_side == Board_Side::left)
		{
			unit_colour = sf::Color::Green;
		}
		else
		{
			unit_colour = sf::Color::Red;
		}

		if (unit.m_side == Board_Side::left)
		{
			unit_x = 0;
		}
		else
		{
			unit_x = sf::VideoMode::getDesktopMode().width - 100.0f;
		}

		if (unit.m_lane == Board_Lane::top)
		{
			unit_y = THIRD_OF_SCREEN_HEIGHT;
		}
		else
		{
			unit_y = THIRD_OF_SCREEN_HEIGHT * 2;
		}

		_Render_Square(unit_colour, unit_x, unit_y);
	}
}

void SFML_Renderer::_render_text()
{
}


void SFML_Renderer::_Render_Square(sf::Color colour, float x, float y)
{
	sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	m_SFML_window->draw(shape);
}