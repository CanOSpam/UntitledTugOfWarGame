// Untitled Tug Of War Game
#include "Precompiled.h"
#include "SFML_Input_Handler.h"
#include "Input_Request.h"

//SFML
#include "SFML/Window/Event.hpp"

SFML_Input_Handler::SFML_Input_Handler(std::shared_ptr<sf::Window> window)
	:input_source(window)
{}

void SFML_Input_Handler::process_to_queue()
{
	// This function should enqueue requests to a common format that the game understands
	// Should also handle input specific to this input type (I.E. closing the window for SFML)
	sf::Event event;
	while (input_source->pollEvent(event))
	{
		// check the type of the event...
		switch (event.type)
		{
			// window closed
		case sf::Event::Closed:
			input_source->close();
			break;

			// key pressed
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Num1)
			{
				player1_lane = Game_Data::Board_Lane::top;
				// UI event to register?
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				player1_lane = Game_Data::Board_Lane::bottom;
				// UI event to register?
			}
			if (event.key.code == sf::Keyboard::Num0)
			{
				player2_lane = Game_Data::Board_Lane::top;
				// UI event to register?
			}
			if (event.key.code == sf::Keyboard::P)
			{
				player2_lane = Game_Data::Board_Lane::bottom;
				// UI event to register?
			}
			if (event.key.code == sf::Keyboard::Z)
			{

				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::left, Game_Data::Unit_Types::light, player1_lane));
			}
			if (event.key.code == sf::Keyboard::X)
			{
				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::left, Game_Data::Unit_Types::medium, player1_lane));
			}
			if (event.key.code == sf::Keyboard::C)
			{
				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::left, Game_Data::Unit_Types::heavy, player1_lane));
			}
			if (event.key.code == sf::Keyboard::Comma)
			{
				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::right, Game_Data::Unit_Types::light, player2_lane));
			}
			if (event.key.code == sf::Keyboard::Period)
			{
				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::right, Game_Data::Unit_Types::medium, player2_lane));
			}
			if (event.key.code == sf::Keyboard::Slash)
			{
				get_queue()->push(std::make_unique<Input_Request_Summon_Unit>(Game_Data::Board_Side::right, Game_Data::Unit_Types::heavy, player2_lane));
			}
			break;

			// key pressed
		case sf::Event::MouseButtonPressed:
			break;

			// we don't process other types of events
		default:
			break;
		}
	}
}