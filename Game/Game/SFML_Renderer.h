#pragma once

// STDLIB
#include <memory>
#include <vector>

// Untitled Tug Of War Game
#include "Unit.h"

// SFML
#include "SFML/Graphics.hpp"

class SFML_Renderer
{
public:
	// Variables

	//Functions
	SFML_Renderer() = delete;
	SFML_Renderer(std::shared_ptr<std::vector<Unit>> left_units, std::shared_ptr<std::vector<Unit>> right_units, std::shared_ptr<sf::RenderWindow> SFML_window);

	void render();

private:
	// Variables
	std::shared_ptr<std::vector<Unit>> _left_units;
	std::shared_ptr<std::vector<Unit>> _right_units;
	std::shared_ptr<sf::RenderWindow> _SFML_window;

	//Functions
	void _render_background();
	void _render_objects();
	void _render_text();
	void _render_unit(Unit& unit);


	void _render_triangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_circle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float size);
	void _render_rectangle(sf::Color outline_colour, sf::Color fill_colour, float outline_thickness, float x, float y, float x_size, float y_size);
};

