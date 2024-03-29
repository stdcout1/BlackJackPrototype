#pragma once
#include "Hand.h"
#include "Deck.h"
class Game
{
private:

	Hand* dh;
	Hand* ph;
	Deck* d;
	double bal;
	double betammount;
public:
	enum states
	{
		INSTANT_LOSS,
		LOSSBYDEALER,
		LOSSBYBUST,
		WINBYBUST,
		WINBYSELF,
		INSTANT_WIN,
		NOT_ENOUGH_MONEY
	};

	enum move_returns
	{
		OK,
		DELEAR16,
		DEALERBUST,
		PLAYERBUST,
	};
	Game();
	~Game();
	Hand* getPlayerPtr() { return ph; }
	Hand* getDealerPtr() { return dh; }
	Deck* getDeckPtr() { return d; }
	double getBal() { return bal; }
	double getBetAmmount() { return betammount; }

	void setDealerPtr(Hand* h) { dh = h; }
	void setPlayerPtr(Hand* h) { ph = h; }
	void setDeckPtr(Deck* nd) { d = nd; }
	double setBal(double b) { bal = b; }
	double setBetAmmount(double ba) { betammount = ba; }

	//mebers
	void show(Hand* ph, Hand* dh);
	char ask();
	move_returns move(bool stand, Hand* ph, Hand* dh, Deck* d); // PLAYERBUST if you cant move after last move...
	void PlayGame();
	void resultofgame();
private:
	states gamestate;
};

