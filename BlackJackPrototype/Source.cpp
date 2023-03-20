#include <iostream>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include <stdio.h>
using namespace std;

const int RETURN_RATE = 1.5;
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


void show(Hand* ph, Hand* dh)
{
	system("cls");
	cout << "Dealers Cards" << endl;
	cout << *dh << endl;
	cout << "Player Hands" << endl;
	cout << *ph << endl;
}



char ask()
{
	cout << "Hit or stand: ";
	char choice;
	cin >> choice;
	return choice;
}


move_returns move(bool stand, Hand* ph, Hand* dh, Deck* d) // PLAYERBUST if you cant move after last move...
{
	if (stand)
	{
		//if standing do dealer logic
		dh->getHandptr()[0]->setFaceup(false);
		d->Draw(dh);
		show(ph, dh);
		if (dh->getHand_Value() > 16)
		{
			return DELEAR16;
		}
		else if (dh->getHand_Value() > 21)
		{
			return DEALERBUST;
		}
		else
		{
			return OK;
		}
	}
	else
	{
		//hit logic for player
		d->Draw(ph);
		show(ph, dh);
		return ph->getHand_Value() > 21 ? PLAYERBUST : OK;
	}
	
}


states PlayGame(int * balance)
{
	Deck* deck = new Deck();
	Hand* phand = new Hand();
	Hand* dhand = new Hand();
	int betamount;
	cout << "Welome to the game" << endl;
	cout << "Enter ammount to bet: ";
	cin >> betamount;
	if (*balance-betamount < 0)
	{
		return NOT_ENOUGH_MONEY;
	}
	cout << "The dealer has:" << endl;
	deck->Draw(dhand);
	deck->Draw(dhand);
	dhand->getHandptr()[0]->setFaceup(true);
	cout << *dhand;
	cout << dhand->getHand_Value() << endl;
	cout << "You have: " << endl;
	deck->Draw(phand);
	deck->Draw(phand);
	cout << *phand;
	cout << phand->getHand_Value() << endl;
	//preflip bj check
	if (phand->getHand_Value() == 21)
	{
		dhand->getHandptr()[0]->setFaceup(false);
		show(phand, dhand);
		return INSTANT_WIN;
	}
	else if (dhand -> getHand_Value() == 21)
	{
		dhand->getHandptr()[0]->setFaceup(false);
		show(phand, dhand);
		return INSTANT_LOSS;
	}

	bool stand = false;
	move_returns cont = OK;
	char choice = 's';
	while (cont == OK)
	{
		if (!stand)
		{
			cout << "Hit or stand: ";
			cin >> choice;
		}
		switch (choice)
		{
			case int('h'):
				cont = move(false, phand, dhand, deck);
				break;
			case int('s'):
				cont = move(true, phand, dhand, deck);
				stand = true;
				break;
			default:
				cout << "Invalid command" << endl;
				break;	
		}
	}
	//after this line no more cards are added

	if (cont == DEALERBUST)
	{
		return WINBYBUST;
	}
	else if (cont == PLAYERBUST)
	{
		return LOSSBYBUST;
	}
	else
	{
		if (dhand->getHand_Value() < phand->getHand_Value())
		{
			return LOSSBYDEALER;
		}
		else
		{
			return WINBYSELF;
		}
	}

};


int main()
{  
	/*
	Card* c = new Card(Card::SPADES, Card::THREE);
	Card* c2 = new Card(Card::SPADES, Card::TWO);
	Card* c3= new Card(Card::SPADES, Card::KING);
	Card* c4 = new Card(Card::SPADES, Card::QUEEN);

	Hand h(c);
	h.add_card(c2);
	h.add_card(c3);
	h.add_card(c4);
	h.remove_card(0);
	
	cout << h;
	cout << h.getHand_Value() << endl;

	Deck* d =  new Deck();

	d->Draw(&h);
	cout << h;
	*/
	srand(time(0));
	int bal = 30;
	states s = PlayGame(&bal);
	return s;
	//Card* c = new Card(Card::SPADES, Card::ACE);
	//Card* c2 = new Card(Card::HEARTS, Card::KING);
	//Card* c3 = new Card(Card::CLUBS, Card::QUEEN);
	
}