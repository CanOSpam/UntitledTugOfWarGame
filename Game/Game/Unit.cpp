// Untitled Tug Of War Game
#include "Precompiled.h"
#include "Unit.h"


Unit::Unit(Game_Data::Unit_Types type, Game_Data::Board_Side side, Game_Data::Board_Lane lane)
	: _type(type)
	, _side(side)
	, _lane(lane)
	, distance(Game_Data::BASE_BUFFER)
	, is_attacking(false)
{
	_initialize();
}

// Allows sorting by distance
// Only works for units on the same side
bool Unit::operator<(const Unit & other_unit)
{
	if (_side == other_unit._side)
	{
		return distance < other_unit.distance;
	}
	else
	{
		throw "Can't compare units from different sides";
	}
}

void Unit::_initialize()
{
	if (_type == Game_Data::Unit_Types::light)
	{
		max_health = 100;
		health = max_health;
		damage = 10;
		armour = 10;
		range = 3.0f;
		base_speed = 2.0f;
		size = 10.0f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::heavy;
	}
	else if (_type == Game_Data::Unit_Types::medium)
	{
		max_health = 200;
		health = max_health;
		damage = 20;
		armour = 20;
		range = 3.0f;
		base_speed = 1.0f;
		size = 10.0f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::light;
	}
	else if (_type == Game_Data::Unit_Types::heavy)
	{
		max_health = 300;
		health = max_health;
		damage = 30;
		armour = 30;
		range = 3.0f;
		base_speed = 0.5f;
		size = 10.0f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::medium;
	}
}
