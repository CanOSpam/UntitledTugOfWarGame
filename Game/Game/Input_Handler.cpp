// Untitled Tug Of War Game
#include "Precompiled.h"
#include "Input_Handler.h"

Input_Handler::Input_Handler()
{
	request_queue = std::make_shared<std::queue<std::unique_ptr<Input_Request>>>();
}

std::shared_ptr<std::queue<std::unique_ptr<Input_Request>>> Input_Handler::get_queue()
{
	return request_queue;
}