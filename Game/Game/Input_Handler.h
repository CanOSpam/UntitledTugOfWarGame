#pragma once

// STDLIB
#include <memory>
#include <queue>

// Untitled Tug Of War Game
#include "Input_Request.h"

class Input_Handler
{
public:
	// Variables

	//Functions
	Input_Handler();
	std::shared_ptr<std::queue<std::unique_ptr<Input_Request>>> get_queue();
	virtual void process_to_queue() = 0;

private:
	// Variables
	std::shared_ptr<std::queue<std::unique_ptr<Input_Request>>> request_queue;

	// Functions
	

};

