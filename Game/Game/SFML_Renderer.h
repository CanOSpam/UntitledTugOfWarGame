#pragma once

// STDLIB
#include <memory>
#include <vector>
#include <unordered_map>

// Untitled Tug Of War Game
#include "Game_Data.h"
#include "Unit.h"
class Player;

// SFML
#include "SFML/Graphics.hpp"

using unit_vec_ptr = std::shared_ptr<std::vector<Unit>>;
using unit_ptr = std::shared_ptr<Unit>;
using window_ptr = std::shared_ptr<sf::RenderWindow>;
using player_ptr = std::shared_ptr<Player>;
using states_ptr = std::shared_ptr<std::unordered_map<Game_Data::Game_States, bool>>;

struct Render_Data
{
	unit_vec_ptr left_units;
	unit_vec_ptr right_units;

	unit_ptr left_base;
	unit_ptr right_base;

	player_ptr left_player;
	player_ptr right_player;

	window_ptr window;

	states_ptr states;
};

struct Unit_Render_Data
{
	Unit unit;
	sf::Image unit_texture_image;
	sf::Texture left_unit_texture;
	sf::Texture right_unit_texture;
	sf::Sprite left_unit_sprite;
	sf::Sprite right_unit_sprite;

	sf::Sprite *unit_sprite;

	Unit_Render_Data(Unit example_unit = Unit(Game_Data::Unit_Types::none, Game_Data::Board_Side::none, Game_Data::Board_Lane::none))
		:unit(std::move(example_unit))
	{
		if (!unit_texture_image.loadFromFile(unit.sprite_path))
		{
			throw "Failed to load unit image";
		}
		right_unit_texture.setSmooth(true);
		right_unit_texture.loadFromImage(unit_texture_image);
		right_unit_sprite.setTexture(right_unit_texture);

		unit_texture_image.flipHorizontally();
		left_unit_texture.setSmooth(true);
		left_unit_texture.loadFromImage(unit_texture_image);
		left_unit_sprite.setTexture(left_unit_texture);

		left_unit_sprite.scale(0.4f, 0.4f);
		right_unit_sprite.scale(0.4f, 0.4f);

		unit_sprite = &left_unit_sprite;
	}

};

struct Unit_Card
{
	std::unique_ptr<sf::Texture> card_texture;
	sf::Sprite card_sprite;

	Unit_Card(std::string card_image_path)
	{
		card_texture = std::make_unique<sf::Texture>();
		if (!card_texture->loadFromFile(card_image_path))
		{
			throw "Failed to load unit card image";
		}

		card_texture->setSmooth(true);
		card_sprite.setTexture(*card_texture);
	}
};

class SFML_Renderer
{
public:
	// Variables

	//Functions
	SFML_Renderer() = delete;
	SFML_Renderer(Render_Data render_data);

	void render();

private:
	// Variables
	const Render_Data _render_data;

	sf::Font _font;
	sf::Text _text;

	std::unordered_map<Game_Data::Unit_Types, std::unique_ptr<Unit_Render_Data>> _example_units;
	std::vector<Unit_Card> _units_cards;

	//Functions
	void _render_background();
	void _render_objects();
	void _render_text();
	void _render_unit(const Unit& unit);
	void _render_unit_cards(const float x, const float y);


	void _render_triangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_circle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_rectangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float x_size, float y_size);
};

