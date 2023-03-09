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
	LOSSBYBUSS,
	WINBYBUST,
	WINBYSELF,
	INSTANT_WIN,
	NOT_ENOUGH_MONEY
};


void show(Hand* ph, Hand* dh)
{
	system("cls");
	cout << "Dealers Cards" << endl;
	cout << *dh << endl;
	cout << "Player Hads" << endl;
	cout << *ph << endl;
}

void move(bool player, Hand* ph, Hand* dh, Deck* d)
{
	bool stand = false;
	char choice;
	cout << "Hit or stand: ";
	cin >> choice;
	switch (choice)
	{
		case int('h') :
			break;
		case int('s') :
			stand = true;
			move(false, ph, dh, d);
			break;
		default:
			cout << "Invalid command" << endl;
			move(player, ph, dh, d);
			break;
	}	
	
	if (player)
	{
		d->Draw(ph);
		while (ph->getHand_Value() < 21 || stand == true)
		{
			show(ph, dh);
			move(player, ph, dh, d);
		}
		return;
	}
	else
	{
		d->Draw(dh);
		while (dh->getHand_Value() < 17)
		{
			show(ph, dh);
			move(player, ph, dh, d);
		}
		return;
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
	cout << "You have: " << endl;
	deck->Draw(phand);
	deck->Draw(phand);
	cout << *phand;
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

	cout << "Hit or stand: ";
	char choice;
	cin >> choice;
	bool invalid = true;
	while (invalid)
	{
		switch (choice)
		{
			case int('h'):
				invalid = false;
				deck->Draw(phand);
				show(phand, dhand);
				move(true, phand, dhand, deck);
				break;
			case int('s'):
				invalid = false;
				deck->Draw(dhand);
				show(phand, dhand);
				move(false, phand, dhand, deck);
				break;
			default:
				cout << "Invalid command" << endl;
				break;	
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
	cout << s;
	//Card* c = new Card(Card::SPADES, Card::ACE);
	//Card* c2 = new Card(Card::HEARTS, Card::KING);
	//Card* c3 = new Card(Card::CLUBS, Card::QUEEN);
	
}