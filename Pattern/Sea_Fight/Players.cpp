#include "Players.h"

condition Aim::fire(std::string cell)
{
	return victim->check(cell);	
}


CompPlayer::CompPlayer() : myFleet(Fleet("computer")), countShips(10)
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

std::shared_ptr<Ship> CompPlayer::returnChips(std::string cell)
{
	return myFleet.returnChips(cell);	
}

std::shared_ptr<Ship> CompPlayer::getKilledShip(std::shared_ptr<Player> p, std::string cell)
{
	return p->returnChips(cell);
}

condition CompPlayer::shot(std::shared_ptr<Player> p, mode mod = Recce)
{
	//some tactics for shot and mod
	std::string cell = "e0";
	Aim shooter(p);
	condition result = shooter.fire(cell);
	//mark shot
	switch(result)
	{
		case Sea:
			shots[cell[1] - '0'][cell[0] - 49 - '0'] = Pop;	
			return result;
		case Wound:
			shots[cell[1] - '0'][cell[0] - 49 - '0'] = Wound;	
			return result;
	}
	//mark killed ships
	auto killedShip = getKilledShip(p, cell);
	
	std::string start = killedShip->getStart();
	std::string end = killedShip->getEnd();
	int startI = start[1] - '0' - 1;
	int startJ = start[0] - 49 - '0' - 1;
	int endI = end[1] - '0' + 1;
	int endJ = end[0] - 49 - '0' + 1;

	if (startI == -1)
		++startI;
	if (startJ == -1)
		++startJ;
	if (endI == 10)
		--endI;
	if (endJ == 10)
		--endJ;
	for (int i = startI; i <= endI; ++i)
	{
		shots[i][startJ] = Wound;
		shots[i][endJ] = Wound;
	}
	for (int j = startJ; j <= endJ; ++j)
	{
		shots[startI][j] = Wound;
		shots[endI][j] = Wound;
	}
	//killedShip->death();	
	return result;
}

condition CompPlayer::check(std::string cell)
{
	return myFleet.check(cell);
}

std::shared_ptr<Ship> HumPlayer::returnChips(std::string cell)
{
	return myFleet.returnChips(cell);	
}

HumPlayer::HumPlayer() : myFleet(Fleet("human")), countShips(10)
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

condition HumPlayer::shot(std::shared_ptr<Player> p)
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

