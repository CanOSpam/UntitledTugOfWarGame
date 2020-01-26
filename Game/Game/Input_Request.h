#pragma once

// Untitled Tug Of War Game
#include "Request_Types.h"
#include "Game_Data.h"

class Input_Request
{
public:
	Input_Request(Game_Events::Request_Types type)
		: _request_type(type)
	{}

	virtual ~Input_Request() {}; // Force class to be recognized as polymorphic

	Game_Events::Request_Types _request_type;
};

class Input_Request_Summon_Unit : public Input_Request
{
public:
	Input_Request_Summon_Unit(Game_Data::Board_Side side, Game_Data::Unit_Types unit_type, Game_Data::Board_Lane lane)
		: _side(side)
		, _unit_type(unit_type)
		, _lane(lane)
		, Input_Request(Game_Events::Request_Types::summon_unit)
	{}

	virtual ~Input_Request_Summon_Unit() override {}; // Force class to be recognized as polymorphic

	Game_Data::Board_Side _side;
	Game_Data::Board_Lane _lane;
	Game_Data::Unit_Types _unit_type;

};

class Input_Request_Toggle_Pause : public Input_Request
{
public:
	Input_Request_Toggle_Pause()
		: Input_Request(Game_Events::Request_Types::toggle_pause)
	{}

	virtual ~Input_Request_Toggle_Pause() override {}; // Force class to be recognized as polymorphic
};

class Input_Request_Add_Upgrade : public Input_Request
{
public:
	Input_Request_Add_Upgrade(Game_Data::Board_Side side, Game_Data::Upgrade_Types upgrade_type)
		: _side(side)
		, _upgrade_type(upgrade_type)
		, Input_Request(Game_Events::Request_Types::add_upgrade)
	{}

	virtual ~Input_Request_Add_Upgrade() override {}; // Force class to be recognized as polymorphic

	Game_Data::Board_Side _side;
	Game_Data::Upgrade_Types _upgrade_type;

};