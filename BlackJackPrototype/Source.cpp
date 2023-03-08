#include <iostream>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
using namespace std;

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
	//Card* c = new Card(Card::SPADES, Card::ACE);
	//Card* c2 = new Card(Card::HEARTS, Card::KING);
	//Card* c3 = new Card(Card::CLUBS, Card::QUEEN);
	Deck* deck = new Deck();
	Hand* phand = new Hand();
	Hand* dhand = new Hand();

	cout << "Welome to the game" << endl;
	cout << "The dealer has:" << endl;
	deck->Draw(dhand);
	deck->Draw(dhand);
	//dhand->add_card(c);
	//dhand->add_card(c2);
	//dhand->add_card(c3);
	dhand->getHandptr()[0]->setFaceup(true);
	
	cout << *dhand ;
	cout << dhand->getHand_Value() << endl;
	cout << "You have: " << endl;
	deck->Draw(phand);
	deck->Draw(phand);
	cout << *phand;
	//preflip bj check
	cout << "Hit or stand: ";
	char choice;
	cin >> choice;
	switch (choice)
	{
	case int('h'):
		cout << "good choice";
		break;
	default:
		cout << "bad choice";
		break;
	}
}