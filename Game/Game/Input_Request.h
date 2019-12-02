#pragma once
#include "Request_Types.h"

class Input_Request
{
public:
	Input_Request(Request_Types type)
		: m_type(type)
	{}

	virtual ~Input_Request() {}; // Force class to be recognized as polymorphic

	Request_Types m_type;
};

class Input_Request_Draw_Square : public Input_Request
{
public:
	Input_Request_Draw_Square(float x, float y)
		: m_x(x), m_y(y), Input_Request(Request_Types::draw_square)
	{}

	virtual ~Input_Request_Draw_Square() override {}; // Force class to be recognized as polymorphic


	float m_x;
	float m_y;
};