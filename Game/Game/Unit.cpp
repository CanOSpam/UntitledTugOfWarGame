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

void Unit::deal_damage(Unit & other_unit)
{
	int damage_dealt = damage - other_unit.armour;

	// Minimum 1 damage if negated by armor
	if (damage_dealt < 1)
	{
		damage_dealt = 1;
	}

	// Double damage if strong against the other type
	if (_strong_against == other_unit._type)
	{
		damage_dealt *= strength_multiplier;
	}

	other_unit.health -= damage_dealt;
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
		current_speed = base_speed;
		size = 10.0f;
		cost = 10;
		strength_multiplier = 2;
		sprite_path = "images/light_unit.png";

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
		current_speed = base_speed;
		size = 10.0f;
		cost = 20;
		strength_multiplier = 2;
		sprite_path = "images/medium_unit.png";

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
		current_speed = base_speed;
		size = 10.0f;
		cost = 30;
		strength_multiplier = 2;
		sprite_path = "images/heavy_unit.png";

		_strong_against = Game_Data::Unit_Types::medium;
	}
	else if (_type == Game_Data::Unit_Types::siege)
	{
		max_health = 100;
		health = max_health;
		damage = 1;
		armour = 0;
		range = 3.0f;
		base_speed = 1.0f;
		current_speed = base_speed;
		size = 10.0f;
		cost = 20;
		strength_multiplier = 100;
		sprite_path = "images/siege_unit.png";

		_strong_against = Game_Data::Unit_Types::base;
	}
	else if (_type == Game_Data::Unit_Types::base)
	{
		// Only base starts at 0
		distance = 0;

		max_health = 5000;
		health = max_health;
		damage = 0;
		armour = 0;
		range = 0.0f;
		base_speed = 0.0f;
		current_speed = base_speed;
		size = 50.0f;
		strength_multiplier = 0;

		_strong_against = Game_Data::Unit_Types::none;
	}
	else
	{
		throw "That unit type doesn't exist!";
	}
}
