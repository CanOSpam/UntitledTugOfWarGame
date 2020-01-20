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
#include <thread>

// Maybe use this?
struct render_data
{
	std::shared_ptr<std::vector<Unit>> left_units;
	std::shared_ptr<std::vector<Unit>> right_units;

	std::shared_ptr<Unit> left_base;
	std::shared_ptr<Unit> right_base;

	std::shared_ptr<Player> left_player;
	std::shared_ptr<Player> right_player;

	std::shared_ptr<sf::RenderWindow> window;
};

int main()
{

	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Game_Data::GAME_SCREEN_WIDTH, Game_Data::GAME_SCREEN_HEIGHT), "Untitled Tug Of War Game", sf::Style::Default);
	
	std::shared_ptr<SFML_Input_Handler> handler = std::make_shared<SFML_Input_Handler>(window);
	std::unique_ptr<Game_Runner> runner = std::make_unique<Game_Runner>(handler);
	std::shared_ptr<std::vector<Unit>> left_units = runner->get_left_units();
	std::shared_ptr<std::vector<Unit>> right_units = runner->get_right_units();
	std::shared_ptr<Unit> left_base = runner->get_left_base();
	std::shared_ptr<Unit> right_base = runner->get_right_base();
	std::unique_ptr<SFML_Renderer> renderer = std::make_unique<SFML_Renderer>(left_units, right_units, left_base, right_base, runner->get_left_player(), runner->get_right_player(), window);

	auto queue = handler->get_queue();

	// General event handling
	while (window->isOpen())
	{
		handler->process_to_queue();

		while (!queue->empty())
		{
			std::unique_ptr<Input_Request> request = std::move(queue->front());
			queue->pop();
			
			if (request->_request_type == Game_Events::Request_Types::summon_unit)
			{
				auto summon_unit_request = dynamic_cast<Input_Request_Summon_Unit&>(*request);
				runner->summon_unit(summon_unit_request._unit_type, summon_unit_request._side, summon_unit_request._lane);
			}
		}

		renderer->render();
		runner->tick();
	}

	return 0;
}
