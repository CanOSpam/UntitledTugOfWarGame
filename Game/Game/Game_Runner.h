#pragma once

// STDLIB
#include <memory>
#include <vector>
#include <chrono>

// Untitled Tug Of War Game
class Unit;

class Game_Runner
{
public:
	// Variables

	// Functions
	Game_Runner();

	void tick();
	std::shared_ptr<std::vector<Unit>> get_left_units();
	std::shared_ptr<std::vector<Unit>> get_right_units();

private:
	// Variables
	std::shared_ptr<std::vector<Unit>> _left_units;
	std::shared_ptr<std::vector<Unit>> _right_units;

	std::chrono::steady_clock::time_point last_tick = std::chrono::high_resolution_clock::now();

	// Functions
	void _unit_tick(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units, Unit& enemy_leader);
	void _unit_tick_no_enemies(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units);
};

