#pragma once
#include "Request_Types.h"
#include "Game_Data.h"

class Input_Request
{
public:
	Input_Request(Request_Types type)
		: m_request_type(type)
	{}

	virtual ~Input_Request() {}; // Force class to be recognized as polymorphic

	Request_Types m_request_type;
};

class Input_Request_Draw_Square : public Input_Request
{
public:
	Input_Request_Draw_Square(float x, float y)
		: m_x(x)
		, m_y(y)
		, Input_Request(Request_Types::draw_square)
	{}

	virtual ~Input_Request_Draw_Square() override {}; // Force class to be recognized as polymorphic


	float m_x;
	float m_y;
};

class Input_Request_Summon_Unit : public Input_Request
{
public:
	Input_Request_Summon_Unit(Board_Side side, Unit_Types unit_type, Board_Lane lane)
		: m_side(side)
		, m_unit_type(unit_type)
		, m_lane(lane)
		, Input_Request(Request_Types::summon_unit)
	{}

	virtual ~Input_Request_Summon_Unit() override {}; // Force class to be recognized as polymorphic

	Board_Side m_side;
	Board_Lane m_lane;
	Unit_Types m_unit_type;

};