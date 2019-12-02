#pragma once

#include <memory>
#include <queue>
#include <mutex>

#include "Input_Request.h"

class Input_Handler
{
public:
	// Variables
	std::mutex queue_mutex;

	//Functions
	Input_Handler();
	std::shared_ptr<std::queue<std::unique_ptr<Input_Request>>> get_queue();
	virtual void process_to_queue() = 0;

private:
	// Variables
	std::shared_ptr<std::queue<std::unique_ptr<Input_Request>>> request_queue; // !!!REMEMBER TO MAKE QUEUE ACCESS THREAD SAFE!!!

	// Functions
	

};

