#pragma once

#include "Fleet.h"
#include <string>


class Player
{
	public:
		//return -1 if sea, 0 if wound, 1 - kill oneDecker, 2 - twoDecker etc.
		virtual int shot(Player* p) = 0;
		virtual int check(std::string cell) = 0;
		virtual void show_fleet() = 0;
		virtual ~Player() {};
	protected:
		Player() {};
};


class Shot
{
	public:
		virtual ~Shot() {};
		virtual void fire(std::string cell) = 0;
	protected:
		Shot(Player* p) : victim(p) {};
		Player* victim;
};

class Aim : public Shot
{
	public:
		Aim(Player* p) : Shot(p) {};
		void fire(std::string cell);
};

class CompPlayer : public Player
{
	public:
		CompPlayer();
		~CompPlayer() {};
		int shot(Player* p);
		int check(std::string cell);
		void show_fleet();
	private:
		Fleet myFleet;
		std::vector<std::vector<int>> shots;
};

class HumPlayer : public Player
{
	public:
		~HumPlayer() {};
		HumPlayer();
		int shot(Player* p);
		int check(std::string cell);
		void show_fleet();
	private:
		Fleet myFleet;
		std::vector<std::vector<int>> shots;
};

