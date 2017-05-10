#pragma once

#include "Fleet.h"
#include <string>

class Player
{
	public:
		virtual condition shot(std::shared_ptr<Player> p, mode mod) = 0;
		virtual condition check(std::string cell) = 0;
		virtual std::shared_ptr<Ship> returnChips(std::string cell) {};
		virtual ~Player() {};
	protected:
		Player() {};
};


class Shot
{
	public:
		virtual condition fire(std::string cell) = 0;
		virtual ~Shot() {};
	protected:
		Shot(std::shared_ptr<Player> p) : victim(p) {};
		std::shared_ptr<Player> victim;
};

class Aim : public Shot
{
	public:
		Aim(std::shared_ptr<Player> p) : Shot(p) {};
		condition fire(std::string cell);
		~Aim() { };
};

class CompPlayer : public Player
{
	public:
		CompPlayer();
		condition shot(std::shared_ptr<Player> p, mode mod);
		//std::shared_ptr<Ship> getKilledShip(Player* p, std::string cell);
		condition check(std::string cell);
		void showFleet();
		~CompPlayer() {};
	private:
		Fleet myFleet;
		std::vector<std::vector<condition>> shots;
};

class HumPlayer : public Player
{
	public:
		HumPlayer();
		condition shot(std::shared_ptr<Player> p, mode mod);
		std::shared_ptr<Ship> returnChips(std::string cell);
		condition check(std::string cell);
		void showFleet();
		~HumPlayer() {};
	private:
		Fleet myFleet;
		std::vector<std::vector<condition>> shots;
};

