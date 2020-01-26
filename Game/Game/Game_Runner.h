#pragma once

// STDLIB
#include <memory>
#include <vector>
#include <chrono>
#include <unordered_map>

// Untitled Tug Of War Game
#include "Game_Data.h"

class Unit;
class SFML_Input_Handler;
class Player;

class Game_Runner
{
public:
	// Variables

	// Functions
	std::shared_ptr<std::vector<Unit>> get_left_units();
	std::shared_ptr<std::vector<Unit>> get_right_units();

	std::shared_ptr<Unit> get_left_base();
	std::shared_ptr<Unit> get_right_base();

	std::shared_ptr<Player> get_left_player();
	std::shared_ptr<Player> get_right_player();

	std::shared_ptr<std::unordered_map<Game_Data::Game_States, bool>> get_game_states();

	Game_Runner(std::shared_ptr<SFML_Input_Handler> input_handler);

	void tick();
	void summon_unit(Game_Data::Unit_Types type, Game_Data::Board_Side side, Game_Data::Board_Lane lane);
	void toggle_pause();
	void add_upgrade(Game_Data::Upgrade_Types type, Game_Data::Board_Side side);

private:
	// Variables
	std::unordered_map<Game_Data::Unit_Types, std::unique_ptr<Unit>> _example_units;

	std::shared_ptr<std::vector<Unit>> _left_units;
	std::shared_ptr<std::vector<Unit>> _right_units;

	std::shared_ptr<Unit> _left_base;
	std::shared_ptr<Unit> _right_base;

	std::shared_ptr<Player> _left_player;
	std::shared_ptr<Player> _right_player;

	std::shared_ptr<SFML_Input_Handler> _input_handler;

	std::chrono::steady_clock::time_point last_tick;

	std::shared_ptr<std::unordered_map<Game_Data::Game_States, bool>> _game_states;

	unsigned long long tick_count;

	// Functions
	void _unit_tick(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units, Unit& enemy_leader);
	void _clean_dead(std::shared_ptr<std::vector<Unit>> units);
	Unit& _get_leader(const Game_Data::Board_Lane lane, const Game_Data::Board_Side side);

};

