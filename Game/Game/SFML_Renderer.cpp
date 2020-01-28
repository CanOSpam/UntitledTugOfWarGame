// Untitled Tug Of War Game
#include "Precompiled.h"
#include "SFML_Renderer.h"
#include "Player.h"
#include "Unit.h"

SFML_Renderer::SFML_Renderer(Render_Data render_data)
	: _render_data(std::move(render_data))
{
	if (!_font.loadFromFile("fonts/officialbook.ttf"))
	{
		throw "Failed to load font";
	}
	_text.setFont(_font);
	_text.setOutlineColor(sf::Color(0, 0, 0, 255));
	_text.setOutlineThickness(2);

	if (!_background_texture.loadFromFile("images/background.png"))
	{
		throw "Failed to load unit card image";
	}

	_background_texture.setSmooth(true);
	_background_sprite.setTexture(_background_texture);
	_background_sprite.scale(2.0f, 2.0f);

	for (Game_Data::Unit_Types type : Game_Data::unit_types_iterable)
	{

		_example_units[type] = std::make_unique<Unit_Render_Data>(Unit(type, Game_Data::Board_Side::none, Game_Data::Board_Lane::none));
	}

	_units_cards.emplace_back("images/light_card.png");
	_units_cards.emplace_back("images/medium_card.png");
	_units_cards.emplace_back("images/heavy_card.png");
	_units_cards.emplace_back("images/siege_card.png");

}

void SFML_Renderer::render()
{
	_render_data.window->clear();
	_render_background();
	_render_objects();
	_render_text();
	_render_data.window->display();
}

void SFML_Renderer::_render_background()
{
	_render_data.window->draw(_background_sprite);
	_render_unit_cards(Game_Data::GAME_SCREEN_WIDTH / 2.0f - (_units_cards[0].card_sprite.getGlobalBounds().width * Game_Data::unit_types_iterable.size()) / 2.0f, Game_Data::GAME_SCREEN_HEIGHT - _units_cards[0].card_sprite.getGlobalBounds().height);
}

void SFML_Renderer::_render_objects()
{
	for (auto&& unit : *_render_data.left_units)
	{
		_render_unit(unit);
	}

	for (auto&& unit : *_render_data.right_units)
	{
		_render_unit(unit);
	}
}

void SFML_Renderer::_render_text()
{
	//General
	_text.setCharacterSize(40);

	float y_padding = 5.0f;

	//Left Health
	_text.setFillColor(sf::Color(0, 153, 51));
	_text.setString("Health: " + std::to_string((int)_render_data.left_base->health));
	_text.setPosition(sf::Vector2f(10.0f, Game_Data::GAME_SCREEN_HEIGHT - y_padding - _text.getCharacterSize() * 2));
	_render_data.window->draw(_text);

	//Right Health
	_text.setString("Health: " + std::to_string((int)_render_data.right_base->health));
	_text.setPosition(sf::Vector2f(Game_Data::GAME_SCREEN_WIDTH - _text.getGlobalBounds().width - 5.0f, Game_Data::GAME_SCREEN_HEIGHT - y_padding - _text.getCharacterSize() * 2));
	_render_data.window->draw(_text);

	//Left Money
	_text.setFillColor(sf::Color(255, 51, 0));
	_text.setString("Berries: " + std::to_string((int)_render_data.left_player->get_money()));
	_text.setPosition(sf::Vector2f(10.0f, Game_Data::GAME_SCREEN_HEIGHT - y_padding - _text.getCharacterSize()));
	_render_data.window->draw(_text);

	//Right Money
	_text.setString("Berries: " + std::to_string((int)_render_data.right_player->get_money()));
	_text.setPosition(sf::Vector2f(Game_Data::GAME_SCREEN_WIDTH - _text.getGlobalBounds().width - 5.0f, Game_Data::GAME_SCREEN_HEIGHT - y_padding - _text.getCharacterSize()));
	_render_data.window->draw(_text);

	//Paused
	if ((*_render_data.states)[Game_Data::Game_States::paused])
	{
		_text.setFillColor(sf::Color(77, 219, 255));
		_text.setString("Game Paused\nPress shift to hire more berry pickers for 100 berries!\nPress space to toggle pause!");
		_text.setPosition(sf::Vector2f(Game_Data::GAME_SCREEN_WIDTH / 2.0f - _text.getGlobalBounds().width / 2.0f, Game_Data::GAME_SCREEN_HEIGHT / 2.0f - _text.getGlobalBounds().height));
		_render_data.window->draw(_text);
	}

	//Game Over
	if ((*_render_data.states)[Game_Data::Game_States::game_over])
	{
		_text.setFillColor(sf::Color::Red);
		_text.setCharacterSize(300);
		_text.setString("Game Over");
		_text.setPosition(sf::Vector2f(10.0f, Game_Data::GAME_SCREEN_HEIGHT / 2.0f - _text.getCharacterSize()));
		_render_data.window->draw(_text);
	}
}

void SFML_Renderer::_render_unit(const Unit& unit)
{
	sf::Color unit_colour;
	float unit_x;
	float unit_y;

	const float THIRD_OF_SCREEN_HEIGHT = ((Game_Data::GAME_SCREEN_HEIGHT / 2.0f) / 3.0f);
	const float BUFFER = 10.0f;

	if (unit._side == Game_Data::Board_Side::left)
	{
		_example_units[unit._type]->unit_sprite = &_example_units[unit._type]->left_unit_sprite;
	}
	else
	{
		_example_units[unit._type]->unit_sprite = &_example_units[unit._type]->right_unit_sprite;
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

	_example_units[unit._type]->unit_sprite->setPosition(sf::Vector2f(unit_x, unit_y));
	_render_data.window->draw(*_example_units[unit._type]->unit_sprite);

	// Health Bar
	float y_offset = 10.0f;
	float bar_x = unit_x;
	float bar_y = unit_y + _example_units[unit._type]->unit_sprite->getGlobalBounds().height + y_offset;
	float bar_x_size = _example_units[unit._type]->unit_sprite->getGlobalBounds().width;
	float bar_y_size = 10.0f;
	_render_rectangle(sf::Color::Blue, sf::Color::Red, 1.0f, bar_x, bar_y, bar_x_size, bar_y_size);
	_render_rectangle(sf::Color::Transparent, sf::Color::Green, 1.0f, bar_x, bar_y, bar_x_size * (unit.health / unit.max_health), bar_y_size);

}

void SFML_Renderer::_render_unit_cards(const float x, const float y)
{
	float x_offset = 0;
	for (auto&& card : _units_cards)
	{
		card.card_sprite.setPosition(x + x_offset, y);
		_render_data.window->draw(card.card_sprite);
		x_offset += card.card_sprite.getGlobalBounds().width;
	}
}

void SFML_Renderer::_render_rectangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float x_size, float y_size)
{
	sf::RectangleShape shape(sf::Vector2f(x_size, y_size));
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_render_data.window->draw(shape);
}

void SFML_Renderer::_render_circle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size)
{
	sf::CircleShape shape(size);
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_render_data.window->draw(shape);
}

void SFML_Renderer::_render_triangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size)
{
	sf::CircleShape shape(size, 3);
	shape.setOutlineColor(outline_colour);
	shape.setOutlineThickness(outline_thickness);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(fill_colour);

	_render_data.window->draw(shape);
}