#include "Precompiled.h"
#include "Unit.h"


Unit::Unit(Unit_Types type, Board_Side side, Board_Lane lane)
	: m_type(type)
	, m_side(side)
	, m_lane(lane)
{
	if (type == Unit_Types::light)
	{
		m_strong_against = Unit_Types::heavy;
	    health = 10;
		damage = 10;
		armour = 10;
		speed = 50.0f;
	}
	else if (type == Unit_Types::medium)
	{
		m_strong_against = Unit_Types::light;
		health = 20;
		damage = 20;
		armour = 20;
		speed = 25.0f;
	}
	else if (type == Unit_Types::heavy)
	{
		m_strong_against = Unit_Types::medium;
		health = 30;
		damage = 30;
		armour = 30;
		speed = 5.0f;
	}
}