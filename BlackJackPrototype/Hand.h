#pragma once
#include "Card.h"
class Hand
{
private:
	Card* handptr[52] = {}; //only 52 cards in a deck..
	int hand_value;
	int num_of_cards;
	
public:
	Hand();
	Hand(Card* c);
	//getters
	int getNumofcards() { return num_of_cards; }
	Card** getHandptr() { return handptr; }
	
	//setters
	void setNumofcards(int c) { num_of_cards = c; } //should never use this...
	void add_card(Card* c);

	int getHand_Value();
	
	//add_card
	//remove_card
	//get value
};

std::ostream& operator<<(std::ostream& stream, Hand h);