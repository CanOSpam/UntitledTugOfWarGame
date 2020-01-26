#pragma once
// Untitled Tug of War Game
#include "Precompiled.h"
#include "SFML_Input_Handler.h"
#include "Game_Runner.h"
#include "Unit.h"
#include "Game.h"
#include "SFML_Renderer.h"

// SFML
#include "SFML/Graphics.hpp"

// STDLIB
#include <memory>
#include <thread>

class Game
{
public:
	// Functions
	Game();
	void run();

	// Variables
	std::shared_ptr<sf::RenderWindow> window;

	std::shared_ptr<SFML_Input_Handler> handler;
	std::unique_ptr<Game_Runner> runner;
	std::shared_ptr<std::vector<Unit>> left_units;
	std::shared_ptr<std::vector<Unit>> right_units;
	std::shared_ptr<Unit> left_base;
	std::shared_ptr<Unit> right_base;
	std::unique_ptr<SFML_Renderer> renderer;
};

