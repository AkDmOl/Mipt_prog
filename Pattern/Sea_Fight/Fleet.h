#pragma once

#include <vector>
#include <string>
#include <memory>

enum condition { Sea, Pop, OneDeckOfShip, Wound, KillOneDeck, KillTwoDeck, KillThreeDeck, KillFourDeck };
enum mode { Recce, Finish };
		
class Ship
{
	public:	
		virtual condition damage() = 0;
		virtual void death() = 0;
		virtual std::string getStart() = 0;
		virtual std::string getEnd() = 0;
		virtual ~Ship() {};
	protected:
		Ship() {};
};

class Cell
{
	public:
		Cell(): cond(Sea), vessel(NULL) {};
		Cell(std::shared_ptr<Ship> ves): cond(OneDeckOfShip), vessel(ves) {};
		void setCond(condition newCond) { cond = newCond; };
		condition getCond() { return cond; };
		std::shared_ptr<Ship> getShip() { return vessel; };
		~Cell() {};
	private:
		condition cond;
		std::shared_ptr<Ship> vessel;
};

class oneDecker: public Ship
{
	public:
		oneDecker(std::string Start): hp(1), start(Start), end(Start) {};
		condition damage();
		void death() { this->~oneDecker(); };
		std::string getStart() { return start; };
		std::string getEnd() { return end; };
		~oneDecker() {};
	private:
		int hp;
		std::string start;
		std::string end;
};

class twoDecker: public Ship
{	
	public:
		twoDecker(std::string Start, std::string End): hp(2), start(Start), end(End) {};
		condition damage();
		void death() { this->~twoDecker(); };
		std::string getStart() { return start; };
		std::string getEnd() { return end; };
		~twoDecker() {};
	private:
		int hp;
		std::string start;
		std::string end;
};

class threeDecker: public Ship
{
	public:
		threeDecker(std::string Start, std::string End): hp(3), start(Start), end(End) {};
		condition damage();
		void death() { this->~threeDecker();};
		std::string getStart() { return start; };
		std::string getEnd() { return end; };
		~threeDecker() {};
	private:
		int hp;
		std::string start;
		std::string end;
};

class fourDecker: public Ship
{
	public:
		fourDecker(std::string Start, std::string End): hp(4), start(Start), end(End) {};
		condition damage();
		void death() { this->~fourDecker(); };
		std::string getStart() { return start; };
		std::string getEnd() { return end; };
		~fourDecker() {};
	private:
		int hp;
		std::string start;
		std::string end;
};


class Fleet
{
	public:
		Fleet(std::string player);
		condition check(std::string cell);
		std::shared_ptr<Ship> returnChips(std::string cell);
		void show(const std::vector<std::vector<condition>> Shots);
	private:
		std::vector<std::vector<Cell>> sea;
};
