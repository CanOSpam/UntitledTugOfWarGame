#pragma once
class Player
{
public:
	// Functions
	Player();
	void tick();
	bool buy(int cost);

	const int get_money();
	void increase_income(int income_increase);

private:
	// Variables
	unsigned int money = 0;
	unsigned int income = 1;
};

