#include <iostream>
#include "Players.cpp"
#include "Fleet.cpp"

int main()
{
	auto comp = std::make_shared<CompPlayer>();
	//HumPlayer human;
	comp->showFleet();
	auto comp2 = std::make_shared<CompPlayer>();
	comp2->showFleet();
	comp->shot(comp2, Recce);
	comp->showFleet();
	return 0;
}
