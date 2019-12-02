#include "Precompiled.h"
#include "SFML_Input_Handler.h"
#include "SFML/Window/Event.hpp"
#include "Input_Request.h"

SFML_Input_Handler::SFML_Input_Handler(std::shared_ptr<sf::Window> window)
	:input_source(window)
{}

void SFML_Input_Handler::process_to_queue()
{
	// This function should enqueue requests to a common format that the game understands
	// Should also handle input specific to this input type (I.E. closing the window for SFML)
	// Should be spun off on a thread
	// !!!REMEMBER TO MAKE QUEUE ACCESS THREAD SAFE!!!
	while (1)
	{
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
				break;

				// key pressed
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					const std::lock_guard<std::mutex> lock(queue_mutex);
					get_queue()->push(std::make_unique<Input_Request_Draw_Square>(event.mouseButton.x, event.mouseButton.y));
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		}
	}
}