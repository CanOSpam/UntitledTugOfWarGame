// Untitled Tug Of War Game
#include "Precompiled.h"
#include "SFML_Renderer.h"
#include "Game_Data.h"

SFML_Renderer::SFML_Renderer(std::shared_ptr<std::vector<Unit>> left_units, std::shared_ptr<std::vector<Unit>> right_units, std::shared_ptr<sf::RenderWindow> SFML_window)
	: _left_units(std::move(left_units))
	, _right_units(std::move(right_units))
	, _SFML_window(std::move(SFML_window))
{
}

void SFML_Renderer::render()
{
	_SFML_window->clear();
	_render_background();
	_render_objects();
	_render_text();
	_SFML_window->display();
}

void SFML_Renderer::_render_background()
{
}

void SFML_Renderer::_render_objects()
{
	for (auto&& unit : *_left_units)
	{
		_render_unit(unit);
	}

	for (auto&& unit : *_right_units)
	{
		_render_unit(unit);
	}
}

void SFML_Renderer::_render_text()
{
}

void SFML_Renderer::_render_unit(Unit& unit)
{
	sf::Color unit_colour;
	float unit_x;
	float unit_y;

	const unsigned int THIRD_OF_SCREEN_HEIGHT = ((Game_Data::GAME_SCREEN_HEIGHT / 2) / 3);
	const float BUFFER = 10.0f;

	if (unit._side == Game_Data::Board_Side::left)
	{
		unit_colour = sf::Color::Green;
	}
	else
	{
		unit_colour = sf::Color::Red;
	}

	if (unit._side == Game_Data::Board_Side::left)
	{
		unit_x = 20.0f + unit.distance + BUFFER;
	}
	else
	{
		unit_x = Game_Data::GAME_SCREEN_WIDTH - 20.0f - BUFFER - unit.distance;
	}

	if (unit._lane == Game_Data::Board_Lane::top)
	{
		unit_y = THIRD_OF_SCREEN_HEIGHT;
	}
	else
	{
		unit_y = THIRD_OF_SCREEN_HEIGHT * 2;
	}

	if (unit._type == Game_Data::Unit_Types::light)
	{
		_render_triangle(unit_colour, unit_x, unit_y);
	}
	else if (unit._type == Game_Data::Unit_Types::medium)
	{
		_render_circle(unit_colour, unit_x, unit_y);
	}
	else if (unit._type == Game_Data::Unit_Types::heavy)
	{
		_render_square(unit_colour, unit_x, unit_y);
	}
	else
	{
		throw "This unit doesn't have a valid type";

	}

}

void SFML_Renderer::_render_square(sf::Color colour, float x, float y)
{
	sf::RectangleShape shape(sf::Vector2f(20.0f, 20.0f));
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	_SFML_window->draw(shape);
}

void SFML_Renderer::_render_circle(sf::Color colour, float x, float y)
{
	sf::CircleShape shape(10.0f);
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	_SFML_window->draw(shape);
}

void SFML_Renderer::_render_triangle(sf::Color colour, float x, float y)
{
	sf::CircleShape shape(10.0f, 3);
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	_SFML_window->draw(shape);
}