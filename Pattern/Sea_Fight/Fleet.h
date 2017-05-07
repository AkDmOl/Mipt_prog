#pragma once

#include <vector>
#include <string>
#include <memory>

class Ship
{
	public:	
		//virtual void debris() = 0;
		virtual int wound() = 0;
		virtual int death() = 0;
		virtual ~Ship() {};
	protected:
		Ship() {};
};

class oneDecker: public Ship
{
	public:
		~oneDecker() {};
		oneDecker(std::string Start): hp(1), start(Start), end(Start) {};
		int wound();
		int death() { return 1; };
	private:
		int hp;
		std::string start;
		std::string end;
};

class twoDecker: public Ship
{	
	public:
		~twoDecker() {};
		twoDecker(std::string Start, std::string End): hp(2), start(Start), end(End) {};
		int wound();
		int death() {return 2;};
	private:
		int hp;
		std::string start;
		std::string end;
};

class threeDecker: public Ship
{
	public:
		~threeDecker() {};
		threeDecker(std::string Start, std::string End): hp(3), start(Start), end(End) {};
		int wound();
		int death() {return 3;};
	private:
		int hp;
		std::string start;
		std::string end;
};

class fourDecker: public Ship
{
	public:
		~fourDecker() {};
		int death() {return 4;};
		int wound();
		fourDecker(std::string Start, std::string End): hp(4), start(Start), end(End) {};
	private:
		int hp;
		std::string start;
		std::string end;
};

class Fleet
{
	public:
		Fleet(std::string player);
		void show();
	private:
		std::vector<std::vector<std::shared_ptr<Ship>>> sea;
};
