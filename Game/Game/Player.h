#pragma once
class Player
{
public:
	// Functions
	Player();
	void tick();
	bool buy(int cost);

	const int get_money();

private:
	// Variables
	unsigned int money = 0;
	unsigned int income = 1;
};

