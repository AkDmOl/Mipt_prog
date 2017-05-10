#include "Fleet.h"
#include <stdlib.h> 
#include <time.h>   

Fleet::Fleet(std::string player)
{
	if (player == "human")
	{
		for (int i = 0; i < 10; ++i){
			std::vector<Cell> row(10);
			sea.push_back(row);
		}

		std::string shipStart;
		std::string shipEnd;
		std::cout << "Введите координату начала 4х-палубника(пример: а0, j0)";
		std::cin >> shipStart;
		std::cout << "Введите координату конца 4х-палубника(пример: а9, j9)";
		std::cin >> shipEnd;
		auto firstShip = std::make_shared<fourDecker>(shipStart, shipEnd);
		Cell fs = Cell(firstShip);	
		if (shipStart[0] == shipEnd[0])
			for (int i = 0; i < 4; ++i)
				sea[shipStart[1] - '0' + i][shipStart[0] - 49 - '0'] = fs;
		else
			for (int i = 0; i < 4; ++i)
				sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + i] = fs;

		for(int i = 0; i < 2; ++i)
		{
			std::cout << "Введите координату начала 3х-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца 3х-палубника";
			std::cin >> shipEnd;
			auto oneMoreShip = std::make_shared<threeDecker>(shipStart, shipEnd);	
			Cell deckOfShip = Cell(oneMoreShip);	
			if (shipStart[0] == shipEnd[0])
				for (int j = 0; j < 3; ++i)
					sea[shipStart[1] - '0' + j][shipStart[0] - 49 - '0'] = deckOfShip;
			else
				for (int j = 0; j < 3; ++i)
					sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + j] = deckOfShip;
		}
		for(int i = 0; i < 3; ++i)
		{
			std::cout << "Введите координату начала 2х-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца 2х-палубника";
			std::cin >> shipEnd;
			auto oneMoreShip = std::make_shared<twoDecker>(shipStart, shipEnd);	
			Cell deckOfShip = Cell(oneMoreShip);	
			if (shipStart[0] == shipEnd[0])
				for (int j = 0; j < 2; ++i)
					sea[shipStart[1] - '0' + j][shipStart[0] - 49 - '0'] = deckOfShip;
			else
				for (int j = 0; j < 2; ++i)
					sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + j] = deckOfShip;
		}
		for (int i = 0; i < 4; ++i)
		{
			std::cout << "Введите координату начала одно-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца одно-палубника";
			std::cin >> shipEnd;
			auto oneMoreShip = std::make_shared<oneDecker>(shipStart);
			Cell deckOfShip = Cell(oneMoreShip);	
			sea[shipStart[1] - '0'][shipStart[0] - 49 - '0'] = deckOfShip;	
		}
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			std::vector<Cell> row(10);
			sea.push_back(row);
		}

		auto firstShip = std::make_shared<fourDecker>("a1", "a4");
		Cell deckOfShip = Cell(firstShip);
		for (int i = 0; i < 4; ++i)
			sea[i][0] = deckOfShip;

		auto secondShip = std::make_shared<threeDecker>("c1", "c3");
		deckOfShip = Cell(secondShip);
		for (int i = 0; i < 3; ++i)
			sea[i][2] = deckOfShip;

		auto thirdShip = std::make_shared<threeDecker>("c5","c7");
		deckOfShip = Cell(thirdShip);
		for (int i = 4; i < 7; ++i)
			sea[i][2] = deckOfShip;

		auto fourthShip = std::make_shared<twoDecker>("a6", "a7");
		deckOfShip = Cell(fourthShip);
		sea[5][0] = deckOfShip;
		sea[6][0] = deckOfShip;

		auto fivthShip = std::make_shared<twoDecker>("a9", "a10");
		deckOfShip = Cell(fivthShip);
		sea[8][0] = deckOfShip;
		sea[9][0] = deckOfShip;

		auto sixthShip = std::make_shared<twoDecker>("c9", "c10");
		deckOfShip = Cell(sixthShip);
		sea[8][2] = deckOfShip;
		sea[9][2] = deckOfShip;

		auto seventhShip = std::make_shared<oneDecker>("e1");
		deckOfShip = Cell(seventhShip);
		sea[0][4] = deckOfShip;

		auto eigthShip = std::make_shared<oneDecker>("e3");
		deckOfShip = Cell(eigthShip);
		sea[2][4] = deckOfShip;
		
		auto ninthShip = std::make_shared<oneDecker>("e5");
		deckOfShip = Cell(ninthShip);
		sea[4][4] = deckOfShip;

		auto tenthShip = std::make_shared<oneDecker>("e7");
		deckOfShip = Cell(tenthShip);
		sea[6][4] = deckOfShip;
	}
}

void Fleet::show(std::vector<std::vector<condition>> Shots)
{
	for (int i = 0; i < 10; ++i)
	{
		for(int j = 0; j < 10; ++j)
		{
			condition cond = sea[i][j].getCond();
			switch(cond)
			{
				case Sea:
					std::cout << "~";
					break;
				case OneDeckOfShip:
					std::cout << "|";
					break;
				case Wound:
					std::cout << "X";
					break;
			}
		}
		std::cout << "			";
		for (int j = 0; j < 10; ++j)
		{
			switch(Shots[i][j])
			{
				case Sea:
					std::cout << "~";
					break;
				case Pop:
					std::cout << "0";
					break;
				case Wound:
					std::cout << "X";
					break;

			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

condition Fleet::check(std::string cell)
{

	condition cond = (sea[cell[1] - '0'][cell[0] - 49 - '0']).getCond();
	switch (cond)
	{
		case Sea:
			return Sea;
		case OneDeckOfShip:
			std::shared_ptr<Ship> curShip =  (sea[cell[1] - '0'][cell[0] - 49 - '0']).getShip();
			return curShip->damage();
	}
}

std::shared_ptr<Ship> Fleet::returnChips(std::string cell)
{
	return (sea[cell[1] - '0'][cell[0] - 49 - '0']).getShip();
}

condition oneDecker::damage()
{
	--hp;
	if (hp == 0)
		return death();
	else
		return Wound;
}

condition twoDecker::damage()
{
	--hp;
	if (hp == 0)
		return death();
	else
		return Wound;
}
condition threeDecker::damage()
{
	--hp;
	if (hp == 0)
		return death();
	else
		return Wound;
}

condition fourDecker::damage()
{
	--hp;
	if (hp == 0)
		return death();
	else
		return Wound;
}
