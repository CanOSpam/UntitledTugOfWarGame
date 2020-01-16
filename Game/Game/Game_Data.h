#pragma once

namespace Game_Data {
	const unsigned int GAME_SCREEN_WIDTH = 1200;
	const unsigned int GAME_SCREEN_HEIGHT = 600;

	enum class Unit_Types
	{
		light,
		medium,
		heavy,

		_count

	};

	enum class Board_Side
	{
		left,
		right,

		_count

	};

	enum class Board_Lane
	{
		top,
		bottom,

		_count

	};
};