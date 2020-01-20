#include "Precompiled.h"
#include "Player.h"


Player::Player()
{
}

void Player::tick()
{
	money += income;
}

bool Player::buy(int cost)
{
	if (cost < money)
	{
		money -= cost;
		return true;
	}
	else
	{
		return false;
	}
}

const int Player::get_money()
{
	return money;
}
