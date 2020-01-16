#pragma once
// Untitled Tug Of War Game
#include "Input_Handler.h"

// SFML
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
	Game_Data::Board_Lane player1_lane = Game_Data::Board_Lane::top;
	Game_Data::Board_Lane player2_lane = Game_Data::Board_Lane::top;

	// Functions
	

};

