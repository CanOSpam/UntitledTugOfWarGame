#pragma once

//STDLIB
#include <vector>

namespace Game_Data {
	const float GAME_SCREEN_WIDTH = 1600;
	const float GAME_SCREEN_HEIGHT = 900;
	const float BASE_BUFFER = 50;

	enum class Unit_Types
	{
		none,

		light,
		medium,
		heavy,
		siege,
		base,

		_count

	};
	const std::vector<Unit_Types> unit_types_iterable{ Unit_Types::light, Unit_Types::medium, Unit_Types::heavy, Unit_Types::siege };

	enum class Upgrade_Types
	{
		none,

		income,

		_count

	};

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

	enum class Game_States
	{
		none,

		paused,
		game_over,

		_count

	};
};