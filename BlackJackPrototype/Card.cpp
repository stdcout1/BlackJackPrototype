#include "Card.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
Card::Card()
{
	display_m = Card::Display(3);
	suit_m = Card::Suit(0);
}
Card::Card(Suit s, Display d)
{
	suit_m = s;
	display_m = d;
}
int Card::getValue()
{
	if (display_m == JACK || display_m == QUEEN || display_m == KING)
	{
		return 10;
	}
	else if (display_m == ACE)
	{
		return 1;
	}
	else 
	{
		return display_m; // auto type cast here
	}
}

string Card::getScreenDisplay()
{
	switch (display_m)
	{
	case 11:
		return "J";
	case 12:
		return "Q";
	case 13:
		return "K";
	case 1:
		return "A";
	default:
		return to_string(display_m);
	}
}

void Card::operator= (const Card c)
{
	display_m = c.display_m;
	suit_m = c.suit_m;
}
bool Card::operator==(const Card c)
{
	if (display_m == c.display_m&&suit_m == c.suit_m) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& stream, Card c)
{
	
	return stream;

}
