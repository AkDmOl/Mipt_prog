#pragma once

#include <vector>
#include <string>
#include <memory>

class Ship
{
	public:	
		virtual void debris() = 0;
		virtual void wound() = 0;
		virtual void death() = 0;
	private:
		int hp;
		std::string start;
		std::string end;

};

class oneDecker : public Ship
{
	public:
		oneDecker(std::string Start): hp(1), start(Start), end(Start) {};
};

class twoDecker : public Ship
{	
	public:
		twoDecker(std::string Start, std::string End): hp(2), start(Start), end(End) {};
};

class threeDecker : public Ship
{
	public:
		treeDecker(std::string Start, std::string End): hp(3), start(Start), end(End) {};
};

class fourDecker : public Ship
{
	public:
		fourDecker(std::string Start, std::string End): hp(4), start(Start), end(End) {};
};

class Fleet
{
	public:
		Fleet(std::string player);
		int generate_map();
		void show();
	private:
		std::vector<std::vector<std::shared_ptr<Ship>>> sea;
}
