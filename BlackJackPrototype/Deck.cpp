#include "Deck.h"

Deck::Deck()
{
	int c = 0;
	for (int s = 3; s < 7; s++) //suits start at three and go up to seven
	{
		for (int v = 1; v < 14; v++)
		{
			Card* card = new Card(Card::Suit(s), Card::Display(v));
			getHandptr()[c] = card;
			c++;
		}
	}
}

Card* Deck::Draw(Hand* h)
{
	// add anti pair
	int rn = rand() % 52 + 1;
	Card* card = getHandptr()[rn];
	if (card == nullptr)
	{
		Draw(h);
	}

	h->add_card(card);
	remove_card(rn);
	return card;
}
