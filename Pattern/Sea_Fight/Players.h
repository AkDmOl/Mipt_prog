#pragma once

#include "Fleet.h"
#include <string>

class Shot
{
	public:
		virtual void aim() = 0;
	protected:
		Player * victim;
		Shot(Player * p) : victim(p) {}
}

class MakeShot : public Shot
{}

class Player
{
	public:
		virtual int shot() = 0;
		virtual int check(std::string cell) = 0;
	private:
		Fleet myFleet;
		std::vector<std::vector<int>> shots;
}

class CompPlayer : public Player
{};

class HumPlayer : public Player
{};

