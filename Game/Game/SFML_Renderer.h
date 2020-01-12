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
	SFML_Renderer(std::shared_ptr<std::vector<Unit>> unit_list_ptr, std::shared_ptr<sf::RenderWindow> SFML_window);

	void render();

private:
	// Variables
	std::shared_ptr<std::vector<Unit>> m_unit_list_ptr;
	std::shared_ptr<sf::RenderWindow> m_SFML_window;

	//Functions
	void _render_background();
	void _render_objects();
	void _render_text();


	void _Render_Square(sf::Color colour, float x, float y);
};

