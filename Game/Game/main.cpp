#include "Precompiled.h"

// Untitled Tug Of War Game
#include "SFML_Input_Handler.h"
#include "SFML_Renderer.h"
#include "Unit.h"

// SFML
#include "SFML/Graphics.hpp"

// STDLIB
#include <memory>

int main()
{

	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height / 2), "Untitled Tug Of War Game", sf::Style::Default);
	SFML_Input_Handler handler(window);

	std::shared_ptr<std::vector<Unit>> unit_list = std::make_shared<std::vector<Unit>>();

	std::unique_ptr<SFML_Renderer> renderer = std::make_unique<SFML_Renderer>(unit_list, window);

	//Make renderer
	float x = 0.0f;
	float y = 0.0f;

	// This should get moved to the renderer
	while (window->isOpen())
	{
		handler.process_to_queue();

		auto queue = handler.get_queue();

		while (!queue->empty())
		{
			std::unique_ptr<Input_Request> request = std::move(queue->front());
			queue->pop();

			if (request->m_request_type == Request_Types::draw_square)
			{
				auto draw_square_request = dynamic_cast<Input_Request_Draw_Square&>(*request);
				x = draw_square_request.m_x;
				y = draw_square_request.m_y;
			}

			if (request->m_request_type == Request_Types::summon_unit)
			{
				auto summon_unit_request = dynamic_cast<Input_Request_Summon_Unit&>(*request);
				unit_list->emplace_back(summon_unit_request.m_unit_type, summon_unit_request.m_side, summon_unit_request.m_lane);
			}
		}

		renderer->render();
	}

	return 0;
}
