#pragma once
// Untitled Tug Of War Game
#include "Game_Data.h"

class Unit
{
public:
	// Functions
	Unit(Game_Data::Unit_Types type, Game_Data::Board_Side side, Game_Data::Board_Lane lane);
	bool operator<(const Unit& other_unit);

	void deal_damage(Unit& other_unit);
	
	//Variables
	float health;
	float max_health;
	int damage;
	int armour;
	float current_speed;
	float base_speed;
	float distance;
	bool is_attacking;
	float range;
	float size;
	int cost;

	Game_Data::Unit_Types _type;
	Game_Data::Board_Side _side;
	Game_Data::Board_Lane _lane;

	Game_Data::Unit_Types _strong_against;

private:
	void _initialize();
};

