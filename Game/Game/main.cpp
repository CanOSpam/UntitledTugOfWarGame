#include "Precompiled.h"

// SFML
#include "SFML/Graphics.hpp"

// Untitled Tug Of War Game
#include "SFML_Input_Handler.h"

// STDLIB
#include <memory>

void RenderSquare(sf::RenderWindow& window, float x, float y);

int main()
{

	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height / 2), "Untitled Tug Of War Game", sf::Style::Default);
	SFML_Input_Handler handler(window);
	SFML_Input_Handler *handler_ptr = &handler;
	std::thread thread(&SFML_Input_Handler::process_to_queue, handler_ptr);

	float x = 0.0f;
	float y = 0.0f;

	// This should get moved to the renderer
	while (window->isOpen())
	{

		const std::lock_guard<std::mutex> lock(handler.queue_mutex);
		auto queue = handler.get_queue();

		while (!queue->empty())
		{
			std::unique_ptr<Input_Request> request = std::move(queue->front());
			queue->pop();

			if (request->m_type == Request_Types::draw_square)
			{
				auto draw_squaure_request = dynamic_cast<Input_Request_Draw_Square&>(*request);
				x = draw_squaure_request.m_x;
				y = draw_squaure_request.m_y;
			}
		}

		window->clear();

		RenderSquare(*window, x, y);
		window->display();
	}

	thread.join();
	return 0;
}

void RenderSquare(sf::RenderWindow& window, float x, float y)
{
	sf::RectangleShape shape(sf::Vector2f(100.0f, 100.0f));
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.0f);
	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}