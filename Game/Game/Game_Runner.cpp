// Untitled Tug Of War Game
#include "Precompiled.h"
#include "Game_Runner.h"
#include "SFML_Input_Handler.h"
#include "Unit.h"
#include "Player.h"

Game_Runner::Game_Runner(std::shared_ptr<SFML_Input_Handler> input_handler)
	: _input_handler(std::move(input_handler))
{
	_left_units = std::make_shared<std::vector<Unit>>();
	_right_units = std::make_shared<std::vector<Unit>>();

	_left_base = std::make_shared<Unit>(Game_Data::Unit_Types::base, Game_Data::Board_Side::left, Game_Data::Board_Lane::none);
	_right_base = std::make_shared<Unit>(Game_Data::Unit_Types::base, Game_Data::Board_Side::right, Game_Data::Board_Lane::none);

	_left_player = std::make_shared<Player>();
	_right_player = std::make_shared<Player>();

	for (Game_Data::Unit_Types type : Game_Data::unit_types_iterable)
	{
		_example_units[type] = std::make_unique<Unit>(type, Game_Data::Board_Side::none, Game_Data::Board_Lane::none);
	}
}

void Game_Runner::tick()
{
	if (std::chrono::high_resolution_clock::now() - last_tick < std::chrono::milliseconds(16))
	{
		return;
	}

	std::sort(_left_units->rbegin(), _left_units->rend());
	std::sort(_right_units->rbegin(), _right_units->rend());
	

	for (std::vector<Unit>::iterator itr = _left_units->begin(); itr < _left_units->end(); ++itr)
	{
		if (itr->_lane == Game_Data::Board_Lane::top)
		{
			Unit& top_right_leader = _get_leader(Game_Data::Board_Lane::top, Game_Data::Board_Side::right);
			_unit_tick(itr, _left_units, top_right_leader);
		}
		else
		{
			Unit& bottom_right_leader = _get_leader(Game_Data::Board_Lane::bottom, Game_Data::Board_Side::right);
			_unit_tick(itr, _left_units, bottom_right_leader);
		}
	}

	for (std::vector<Unit>::iterator itr = _right_units->begin(); itr < _right_units->end(); ++itr)
	{
		if (itr->_lane == Game_Data::Board_Lane::top)
		{
			Unit& top_left_leader = _get_leader(Game_Data::Board_Lane::top, Game_Data::Board_Side::left);
			_unit_tick(itr, _right_units, top_left_leader);
		}
		else
		{
			Unit& bottom_left_leader = _get_leader(Game_Data::Board_Lane::bottom, Game_Data::Board_Side::left);
			_unit_tick(itr, _right_units, bottom_left_leader);
		}
	}

	_clean_dead(_left_units);
	_clean_dead(_right_units);

	_left_player->tick();
	_right_player->tick();

	//TODO: Check for game end and send event if detected
	if (_left_base->health <= 0 || _right_base->health <= 0)
	{
		exit(0);
	}


	last_tick = std::chrono::high_resolution_clock::now();
}

void Game_Runner::summon_unit(Game_Data::Unit_Types type, Game_Data::Board_Side side, Game_Data::Board_Lane lane)
{
	if (side == Game_Data::Board_Side::left)
	{
		if (_left_player->buy(_example_units[type]->cost))
		{
			_left_units->emplace_back(type, side, lane);
		}
	}
	else if (side == Game_Data::Board_Side::right)
	{
		if (_right_player->buy(_example_units[type]->cost))
		{
			_right_units->emplace_back(type, side, lane);
		}
	}
	else
	{
		throw "Something went wrong with the sidedness of this unit";
	}
}

std::shared_ptr<std::vector<Unit>> Game_Runner::get_left_units()
{
	return _left_units;
}

std::shared_ptr<std::vector<Unit>> Game_Runner::get_right_units()
{
	return _right_units;
}

std::shared_ptr<Unit> Game_Runner::get_left_base()
{
	return _left_base;
}

std::shared_ptr<Unit> Game_Runner::get_right_base()
{
	return _right_base;
}

std::shared_ptr<Player> Game_Runner::get_left_player()
{
	return _left_player;
}

std::shared_ptr<Player> Game_Runner::get_right_player()
{
	return _right_player;
}

void Game_Runner::_unit_tick(std::vector<Unit>::iterator& unit, std::shared_ptr<std::vector<Unit>> units, Unit& enemy_leader)
{
	// Move to enemy base
	unit->distance += unit->current_speed;

	// Stop if hit another unit or base
	if (unit->distance + enemy_leader.distance + unit->range + (unit->size * 2) + (enemy_leader.size * 2) >= Game_Data::GAME_SCREEN_WIDTH - (Game_Data::BASE_BUFFER * 2))
	{
		unit->current_speed = 0;
		unit->is_attacking = true;

		unit->deal_damage(enemy_leader);
	}
	else
	{
		unit->current_speed = unit->base_speed;
		unit->is_attacking = false;
	}
}

void Game_Runner::_clean_dead(std::shared_ptr<std::vector<Unit>> units)
{
	for (std::vector<Unit>::iterator itr = units->begin(); itr < units->end();)
	{
		// Clean up dead units
		if (itr->health <= 0)
		{
			itr = units->erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

Unit& Game_Runner::_get_leader(const Game_Data::Board_Lane lane, const Game_Data::Board_Side side)
{
	std::shared_ptr<std::vector<Unit>> units = side == Game_Data::Board_Side::left ? _left_units : _right_units;

	for (auto&& unit : *units)
	{
		if (unit._lane == lane && unit.health > 0)
		{
			return unit;
		}
	}

	return side == Game_Data::Board_Side::left ? *_left_base : *_right_base;
}