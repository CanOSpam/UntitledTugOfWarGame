// Untitled Tug Of War Game
#include "Precompiled.h"
#include "SFML_Input_Handler.h"
#include "SFML_Renderer.h"
#include "Game_Runner.h"
#include "Unit.h"

// SFML
#include "SFML/Graphics.hpp"

// STDLIB
#include <memory>

int main()
{

	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Game_Data::GAME_SCREEN_WIDTH, Game_Data::GAME_SCREEN_HEIGHT), "Untitled Tug Of War Game", sf::Style::Default);
	
	std::unique_ptr<SFML_Input_Handler> handler = std::make_unique<SFML_Input_Handler>(window);
	std::unique_ptr<Game_Runner> runner = std::make_unique<Game_Runner>();
	std::shared_ptr<std::vector<Unit>> left_units = runner->get_left_units();
	std::shared_ptr<std::vector<Unit>> right_units = runner->get_right_units();
	std::unique_ptr<SFML_Renderer> renderer = std::make_unique<SFML_Renderer>(left_units, right_units, window);

	// General event handling
	while (window->isOpen())
	{
		handler->process_to_queue();

		auto queue = handler->get_queue();

		while (!queue->empty())
		{
			std::unique_ptr<Input_Request> request = std::move(queue->front());
			queue->pop();
			
			if (request->_request_type == Game_Events::Request_Types::summon_unit)
			{
				auto summon_unit_request = dynamic_cast<Input_Request_Summon_Unit&>(*request);

				if (summon_unit_request._side == Game_Data::Board_Side::left)
				{
					left_units->emplace_back(summon_unit_request._unit_type, summon_unit_request._side, summon_unit_request._lane);
				}
				else if (summon_unit_request._side == Game_Data::Board_Side::right)
				{
					right_units->emplace_back(summon_unit_request._unit_type, summon_unit_request._side, summon_unit_request._lane);
				}
				else
				{
					throw "Something went wrong with the sidedness of this unit";
				}
			}
		}

		renderer->render();
		runner->tick();
	}

	return 0;
}
