#include <Fleet.h>
#include <stdlib.h> 
#include <time.h>   

fourDecker::fourDecker()

Fleet::Fleet(std::string player)
{
	if (player == "Human")
	{
		for (int i = 0; i < 10; ++i){
			std::vector<std::shared_ptr<Ship>> row(10);
			sea.push_back(row);
		}

		std::string shipStart;
		std::string shipEnd;
		std::cout << "Введите координату начала 4х-палубника(пример: а0, j0)";
		std::cin >> shipStart;
		std::cout << "Введите координату конца 4х-палубника(пример: а9, j9)";
		std::cin >> shipEnd;
		std::shared_ptr<fourDecker> firstShip(new fourDecker(shipStart, shipEnd));	
		if (shipStart[0] == shipEnd[0])
			for (int i = 0; i < 4; ++i)
				sea[shipStart[1] - '0' + i][shipStart[0] - 49 - '0'] = firstShip;
		else
			for (int i = 0; i < 4; ++i)
				sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + i] = firstShip;

		for(int i = 0; i < 2; ++i)
		{
			std::cout << "Введите координату начала 3х-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца 3х-палубника";
			std::cin >> shipEnd;
			std::shared_ptr<threeDecker> oneMoreShip(new threeDecker(shipStart, shipEnd));	
			if (shipStart[0] == shipEnd[0])
				for (int j = 0; j < 3; ++i)
					sea[shipStart[1] - '0' + j][shipStart[0] - 49 - '0'] = oneMoreShip;
			else
				for (int j = 0; j < 3; ++i)
					sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + j] = oneMoreShip;
		}
		for(int i = 0; i < 3; ++i)
		{
			std::cout << "Введите координату начала 2х-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца 2х-палубника";
			std::cin >> shipEnd;
			std::shared_ptr<twoDecker> oneMoreShip(new twoDecker(shipStart, shipEnd));	
			if (shipStart[0] == shipEnd[0])
				for (int j = 0; j < 2; ++i)
					sea[shipStart[1] - '0' + j][shipStart[0] - 49 - '0'] = oneMoreShip;
			else
				for (int j = 0; j < 2; ++i)
					sea[shipStart[1] - '0'][shipStart[0] - 49 - '0' + j] = oneMoreShip;
		}
		for (int i = 0; i < 4; ++i)
		{
			std::cout << "Введите координату начала одно-палубника";
			std::cin >> shipStart;
			std::cout << "Введите координату конца одно-палубника";
			std::cin >> shipEnd;
			std::shared_ptr<oneDecker> oneMoreShip(new oneDecker(shipStart, shipEnd));
			sea[shipStart[1] - '0'][shipStart[0] - 49 - '0'] = oneMoreShip;	
		}
	}
	else
	{
		std::shared_ptr<fourDecker> firstShip(new fourDecker("a1", "a4"));
		std::shared_ptr<threeDecker> secondShip(new threeDecker("c1", "c3"));
		std::shared_ptr<threeDecker> thirdShip(new threeDecker("c5","c7"));
		std::shared_ptr<twoDecker> fourthShip(new twoDecker("a6", "a7"));
		std::shared_ptr<twoDecker> fivthShip(new twoDecker("a9", "a10"));
		std::shared_ptr<twoDecker> sixthShip(new twoDecker("c9", "c10"));
		std::shared_ptr<oneDecker> seventhShip(new oneDecker("e1"));
		std::shared_ptr<oneDecker> eigthShip(new oneDecker("e3"));
		std::shared_ptr<oneDecker> ninthShip(new oneDecker("e5"));
		std::shared_ptr<oneDecker> tenthShip(new oneDecker("e7"));
		for (int i = 0; i < 10; ++i)
		{
			std::vector<std::shared_ptr<Ship>> row(10);
			sea.push_back(row);
		}
		for (int i = 0; i < 4; ++i)
			sea[i][0] = firstShip;

		for (int i = 0; i < 3; ++i)
			sea[i][2] = secondShip;
		for (int i = 4; i < 7; ++i)
			sea[i][2] = thirdShip;
		
		sea[5][0] = fourthShip;
		sea[6][0] = fourthShip;

		sea[8][0] = fivthShip;
		sea[9][0] = fivthShip;

		sea[8][2] = sixthShip;
		sea[9][2] = sixthShip;

		sea[0][4] = seventhShip;
		sea[2][4] = eigthShip;
		sea[4][4] = ninthShip;
		sea[6][4] = tenthShip;
	}
}
