#pragma once

// STDLIB
#include <memory>
#include <vector>

// Untitled Tug Of War Game
#include "Unit.h"

class Player;

// SFML
#include "SFML/Graphics.hpp"

using unit_vec_ptr = std::shared_ptr<std::vector<Unit>>;
using unit_ptr = std::shared_ptr<Unit>;
using window_ptr = std::shared_ptr<sf::RenderWindow>;
using player_ptr = std::shared_ptr<Player>;

class SFML_Renderer
{
public:
	// Variables

	//Functions
	SFML_Renderer() = delete;
	SFML_Renderer(unit_vec_ptr left_units, unit_vec_ptr right_units, unit_ptr left_base, unit_ptr right_base, player_ptr left_player, player_ptr right_player, std::shared_ptr<sf::RenderWindow> SFML_window);

	void render();

private:
	// Variables
	const unit_vec_ptr _left_units;
	const unit_vec_ptr _right_units;
	const unit_ptr _left_base;
	const unit_ptr _right_base;
	const player_ptr _left_player;
	const player_ptr _right_player;

	sf::Font _font;

	window_ptr _SFML_window;

	//Functions
	void _render_background();
	void _render_objects();
	void _render_text();
	void _render_unit(Unit& unit);


	void _render_triangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_circle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_rectangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float x_size, float y_size);
};

