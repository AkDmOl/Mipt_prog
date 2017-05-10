#include <iostream>
#include "Players.cpp"
#include "Fleet.cpp"

int main()
{
	//add toss
	auto player1 = std::make_shared<CompPlayer>();
	//comp->showFleet();
	auto player2 = std::make_shared<CompPlayer>();
	
	//MAIN GAME 
	//Steps for human will be little difference
	/*
	while(player1->getCountShips() > 0 && player2->getCountShips() > 0)
	{
		condition result = player1->shot(player2);
		while (result == Wound)
		{
			result = player1->shot(player2, Finish);
			if (result == KillOneDeck || result == KillTwoDeck || result == KillThreeDeck || result == KillFourDeck)
				result = player1->shot(player2);
		}
		if (player2->getCountShips() > 0)
		{
			condition result = player2->shot(player1);
			while (result == Wound)
			{
				result = player2->shot(player1, Finish);
				if (result == KillOneDeck || result == KillTwoDeck || result == KillThreeDeck || result == KillFourDeck)
					result = player2->shot(player1);
			}
		}	
	}
	*/

	player1->shot(player2);
	player1->showFleet();
	player2->showFleet();
	return 0;
}
