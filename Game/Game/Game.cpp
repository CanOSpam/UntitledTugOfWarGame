#include "Precompiled.h"
#include "Game.h"

Game::Game()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(Game_Data::GAME_SCREEN_WIDTH, Game_Data::GAME_SCREEN_HEIGHT), "Untitled Tug Of War Game", sf::Style::Default);

	handler = std::make_shared<SFML_Input_Handler>(window);
	runner = std::make_unique<Game_Runner>(handler);

	Render_Data render_data;
	render_data.left_units = runner->get_left_units();
	render_data.right_units = runner->get_right_units();

	render_data.left_base = runner->get_left_base();
	render_data.right_base = runner->get_right_base();

	render_data.left_player = runner->get_left_player();
	render_data.right_player = runner->get_right_player();

	render_data.window = window;

	render_data.states = runner->get_game_states();

	renderer = std::make_unique<SFML_Renderer>(render_data);
}

void Game::run()
{
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
			else if (request->_request_type == Game_Events::Request_Types::toggle_pause)
			{
				runner->toggle_pause();
			}
			else if (request->_request_type == Game_Events::Request_Types::add_upgrade)
			{
				auto add_upgrade_request = dynamic_cast<Input_Request_Add_Upgrade&>(*request);
				runner->add_upgrade(add_upgrade_request._upgrade_type, add_upgrade_request._side);
			}
		}

		renderer->render();
		runner->tick();
	}
}