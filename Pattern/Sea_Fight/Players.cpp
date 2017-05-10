#include "Players.h"

condition Aim::fire(std::string cell)
{
	return victim->check(cell);	
}


CompPlayer::CompPlayer() : myFleet(Fleet("computer"))
{
	for (int i = 0; i < 10; ++i)
	{
		std::vector<condition> row(10, Sea);
		shots.push_back(row);
	}	
}

void CompPlayer::showFleet()
{
	myFleet.show(shots);
}
/*
std::shared_ptr<Ship> CompPlayer::getKilledShip(Player* p, std::string cell)
{
	return p->returnChips(cell);
}
*/
condition CompPlayer::shot(std::shared_ptr<Player> p, mode mod)
{
	//some tactics for shot and mod
	std::string cell = "a0";
	Aim shooter(p);
	condition result = shooter.fire(cell);
	//mark shot
	switch(result)
	{
		case Sea:
			shots[cell[1] - '0'][cell[0] - 49 - '0'] = Pop;	
			return result;
		case Wound:
			shots[cell[1] - '0'][cell[0] - 49 - '0'] = result;	
			return result;
	}
	
	//mark killed ship
	//std::shared_ptr<Ship> killedShip = getKilledShip(p, cell);
	return Sea;
}

condition CompPlayer::check(std::string cell)
{
	return myFleet.check(cell);
}

std::shared_ptr<Ship> HumPlayer::returnChips(std::string cell)
{
	return myFleet.returnChips(cell);	
}

HumPlayer::HumPlayer() : myFleet(Fleet("human")) 
{
	for (int i = 0; i < 10; ++i)
	{
		std::vector<condition> row(10,Sea);
		shots.push_back(row);
	}	
}

void HumPlayer::showFleet()
{
	myFleet.show(shots);
}

condition HumPlayer::shot(std::shared_ptr<Player> p, mode mod)
{

	std::string cell;
	std::cin >> cell;
	Aim shooter(p);
	condition result = shooter.fire(cell);
	//mark shot	
	if ( result == Sea)
		shots[cell[1] - '0'][cell[0] - 49 - '0'] = Pop;
	else
		shots[cell[1] - '0'][cell[0] - 49 - '0'] = Wound;
	return result;
}

condition HumPlayer::check(std::string cell)
{
	return myFleet.check(cell);
}

