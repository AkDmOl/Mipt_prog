#include "Players.h"

void Aim::fire(std::string cell)
{
	victim->check(cell);	
}


CompPlayer::CompPlayer() : myFleet(Fleet("computer")) {};

void CompPlayer::show_fleet()
{
	myFleet.show();
}

int CompPlayer::shot(Player* p)
{
	//some tactics for shot
	std::string cell;
	Aim shooter(p);
	return shooter.fire(cell);
}

int CompPlayer::check(std::string cell)
{
	return 0;
}

int HumPlayer::check(std::string cell)
{
	return 0;
}

int HumPlayer::shot(Player* p)
{
	//some tactics for shot
	std::string cell;
	Aim shooter(p);
	return shooter.fire(cell);
}

HumPlayer::HumPlayer() : myFleet(Fleet("human")) {};

void HumPlayer::show_fleet()
{
	myFleet.show();
}
