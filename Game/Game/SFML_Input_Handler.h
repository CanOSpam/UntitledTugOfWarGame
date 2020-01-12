#pragma once
#include "Input_Handler.h"
#include "SFML/Window/Window.hpp"

class SFML_Input_Handler : public Input_Handler
{
public:
	// Functions
	SFML_Input_Handler() = delete;
	SFML_Input_Handler(std::shared_ptr<sf::Window> window);
	virtual void process_to_queue() override;

	// Variables

private:
	// Variables
	std::shared_ptr<sf::Window> input_source;
	Board_Lane player1_lane = Board_Lane::top;
	Board_Lane player2_lane = Board_Lane::top;

	// Functions
	

};

