#pragma once
#include "Game_Data.h"

class Unit
{
public:
	Unit(Unit_Types type, Board_Side side, Board_Lane lane);

	// Move this to an external definition format, JSON?
	int health;
	int damage;
	int armour;
	float speed;

	Unit_Types m_type;
	Board_Side m_side;
	Board_Lane m_lane;

	Unit_Types m_strong_against;
};

