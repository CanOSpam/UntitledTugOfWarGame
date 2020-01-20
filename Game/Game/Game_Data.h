#pragma once

//STDLIB
#include <vector>

namespace Game_Data {
	const unsigned int GAME_SCREEN_WIDTH = 1200;
	const unsigned int GAME_SCREEN_HEIGHT = 600;
	const unsigned int BASE_BUFFER = 50;

	enum class Unit_Types
	{
		none,

		light,
		medium,
		heavy,
		base,

		_count

	};

	const std::vector<Unit_Types> unit_types_iterable{ Unit_Types::light, Unit_Types::medium, Unit_Types::heavy };

	enum class Board_Side
	{
		none,

		left,
		right,

		_count

	};

	enum class Board_Lane
	{
		none,

		top,
		bottom,

		_count

	};
};