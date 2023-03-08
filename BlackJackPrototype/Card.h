#pragma once
#include <iostream>
class Card
{
public:
	static const int CARD_WIDTH = 15;
	static const int CARD_HEIGHT = 8;
	enum Suit { HEARTS = 3, DIAMONDS, CLUBS, SPADES };
	enum Display { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
	Card(Suit s, Display d);
	Card(); // not allowed to specificy initlizer for arrays 
	//getters
	Suit getSuit() { return suit_m; }
	Display getDisplay() { return display_m; }
	bool getFaceup() { return faceup; }
	//setters
	void setSuit(int s) { suit_m = Suit(s); }
	void setDisplay(int d) { display_m = Display(d); }
	void setFaceup(bool f) { faceup = f; }
	//member
	int getValue();
	std::string getScreenDisplay();
	//overload
	void operator= (const Card c);
	bool operator==(const Card c);
private:
	Suit suit_m;
	Display display_m;
	bool faceup = false;
};

std::ostream& operator<<(std::ostream&, Card c);

