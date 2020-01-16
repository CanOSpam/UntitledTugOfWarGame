// Untitled Tug Of War Game
#include "Precompiled.h"
#include "Game_Runner.h"
#include "Unit.h"

// STDLIB
#include <algorithm>


Game_Runner::Game_Runner()
{
	_left_units = std::make_shared<std::vector<Unit>>();
	_right_units = std::make_shared<std::vector<Unit>>();
}

void Game_Runner::tick()
{
	if (std::chrono::high_resolution_clock::now() - last_tick < std::chrono::milliseconds(16))
	{
		return;
	}

	std::sort(_left_units->rbegin(), _left_units->rend());
	std::sort(_right_units->rbegin(), _right_units->rend());


	


	for (std::vector<Unit>::iterator itr = _left_units->begin(); itr < _left_units->end();)
	{
		if (_right_units->size() > 0)
		{
			Unit& right_leader = *_right_units->begin();
			_unit_tick(itr, _left_units, right_leader);
		}
		else
		{
			_unit_tick_no_enemies(itr, _left_units);
		}
	}

	for (std::vector<Unit>::iterator itr = _right_units->begin(); itr < _right_units->end();)
	{
		if (_left_units->size() > 0)
		{
			Unit& left_leader = *_left_units->begin();
			_unit_tick(itr, _right_units, left_leader);
		}
		else
		{
			_unit_tick_no_enemies(itr, _right_units);
		}
	}

	last_tick = std::chrono::high_resolution_clock::now();
}

std::shared_ptr<std::vector<Unit>> Game_Runner::get_left_units()
{
	return _left_units;
}

std::shared_ptr<std::vector<Unit>> Game_Runner::get_right_units()
{
	return _right_units;
}

void Game_Runner::_unit_tick(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units, Unit& enemy_leader)
{
	// Move to enemy base
	unit->distance += unit->current_speed;
	if (unit->distance >= Game_Data::GAME_SCREEN_WIDTH - 50.0f) {
		unit->distance = Game_Data::GAME_SCREEN_WIDTH - 50.0f;
		unit->current_speed = 0;

		// TEST
		unit->health = 0;
	}


	if (unit->distance + enemy_leader.distance + unit->range + (unit->size * 2) + (enemy_leader.size * 2) >= Game_Data::GAME_SCREEN_WIDTH - (Game_Data::BASE_BUFFER * 2))
	{
		unit->current_speed = 0;

		int damage = unit->damage - enemy_leader.armour;
		if (damage < 1)
		{
			damage = 1;
		}

		enemy_leader.health -= damage;
	}
	else
	{
		unit->current_speed = unit->base_speed;
	}


	// Clean up dead units
	if (unit->health <= 0)
	{
		unit = units->erase(unit);
	}
	else
	{
		++unit;
	}
}


void Game_Runner::_unit_tick_no_enemies(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units)
{
	// Move to enemy base
	unit->current_speed = unit->base_speed;
	unit->distance += unit->current_speed;
	if (unit->distance >= Game_Data::GAME_SCREEN_WIDTH - 50.0f) {
		unit->distance = Game_Data::GAME_SCREEN_WIDTH - 50.0f;
		unit->current_speed = 0;

		// TEST
		unit->health = 0;
	}

	// Clean up dead units
	if (unit->health <= 0)
	{
		unit = units->erase(unit);
	}
	else
	{
		++unit;
	}
}