// Untitled Tug Of War Game
#include "Precompiled.h"
#include "SFML_Renderer.h"
#include "Game_Data.h"
#include "Player.h"

SFML_Renderer::SFML_Renderer(unit_vec_ptr left_units, unit_vec_ptr right_units, unit_ptr left_base, unit_ptr right_base, player_ptr left_player, player_ptr right_player, std::shared_ptr<sf::RenderWindow> SFML_window)
	: _left_units(std::move(left_units))
	, _right_units(std::move(right_units))
	, _left_base(std::move(left_base))
	, _right_base(std::move(right_base))
	, _left_player(std::move(left_player))
	, _right_player(std::move(right_player))
	, _SFML_window(std::move(SFML_window))
{
	if (!_font.loadFromFile("fonts/mandalore.ttf"))
	{
		throw "Failed to load font";
	}
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
	//General
	sf::Text text;
	text.setFont(_font);
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Underlined);

	//Left Health
	text.setFillColor(sf::Color::Green);
	text.setPosition(sf::Vector2f(10.0f, 10.0f));
	text.setString(std::to_string((int)_left_base->health));
	_SFML_window->draw(text);

	//Right Health
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(Game_Data::GAME_SCREEN_WIDTH - 70.0f, 10.0f));
	text.setString(std::to_string((int)_right_base->health));
	_SFML_window->draw(text);

	//Left Money
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(sf::Vector2f(10.0f, Game_Data::GAME_SCREEN_HEIGHT - 40.0f));
	text.setString(std::to_string((int)_left_player->get_money()));
	_SFML_window->draw(text);

	//Right Money
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(sf::Vector2f(Game_Data::GAME_SCREEN_WIDTH - 70.0f, Game_Data::GAME_SCREEN_HEIGHT - 40.0f));
	text.setString(std::to_string((int)_right_player->get_money()));
	_SFML_window->draw(text);
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
		_render_triangle(unit_colour, unit_colour, 1.0f, unit_x, unit_y, unit.size);
	}
	else if (unit._type == Game_Data::Unit_Types::medium)
	{
		_render_circle(unit_colour, unit_colour, 1.0f, unit_x, unit_y, unit.size);
	}
	else if (unit._type == Game_Data::Unit_Types::heavy)
	{
		_render_rectangle(unit_colour, unit_colour, 1.0f, unit_x, unit_y, unit.size * 2, unit.size * 2);
	}
	else
	{
		throw "This unit doesn't have a valid type";

	}

	// Health Bar
	float double_unit_size = unit.size * 2;
	float y_offset = double_unit_size + 5.0f;
	float bar_x = unit_x - 10.f;
	float bar_y = unit_y + y_offset;
	float bar_x_size = double_unit_size * 2.0f;
	float bar_y_size = 10.0f;
	_render_rectangle(sf::Color::Blue, sf::Color::Red, 1.0f, bar_x, bar_y, bar_x_size, bar_y_size);
	_render_rectangle(sf::Color::Transparent, sf::Color::Green, 1.0f, bar_x, bar_y, bar_x_size * (unit.health / unit.max_health), bar_y_size);

}

void SFML_Renderer::_render_rectangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float x_size, float y_size)
{
	sf::RectangleShape shape(sf::Vector2f(x_size, y_size));
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_SFML_window->draw(shape);
}

void SFML_Renderer::_render_circle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size)
{
	sf::CircleShape shape(size);
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_SFML_window->draw(shape);
}

void SFML_Renderer::_render_triangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size)
{
	sf::CircleShape shape(size, 3);
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_SFML_window->draw(shape);
}