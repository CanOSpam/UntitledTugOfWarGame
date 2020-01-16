// Untitled Tug Of War Game
#include "Precompiled.h"
#include "Unit.h"


Unit::Unit(Game_Data::Unit_Types type, Game_Data::Board_Side side, Game_Data::Board_Lane lane)
	: _type(type)
	, _side(side)
	, _lane(lane)
	, distance(0)
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
		health = 100;
		damage = 10;
		armour = 10;
		range = 3.0f;
		base_speed = 2.0f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::heavy;
	}
	else if (_type == Game_Data::Unit_Types::medium)
	{
		health = 200;
		damage = 20;
		armour = 20;
		range = 3.0f;
		base_speed = 1.0f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::light;
	}
	else if (_type == Game_Data::Unit_Types::heavy)
	{
		health = 300;
		damage = 30;
		armour = 30;
		range = 3.0f;
		base_speed = 0.5f;
		current_speed = base_speed;

		_strong_against = Game_Data::Unit_Types::medium;
	}
}
