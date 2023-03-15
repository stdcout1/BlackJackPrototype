#include "Hand.h"
#include <iostream>
#include <iomanip>
using namespace std;

Hand::Hand()
{
	hand_value = 0;
	num_of_cards = 0;
}

Hand::Hand(Card * c)
{
	hand_value = 0;
	num_of_cards = 0;
	handptr[num_of_cards] = c;
	num_of_cards++;
}
void Hand::copy(Card** source, Card** dest, int ignore_pos)
{
	//manual deep copy
	for (int i = 0,v = 0; i < num_of_cards; i++,v++)
	{
		//cout << i;
		if (i == ignore_pos)// dont include ignore pos?
		{
			delete (source[i]); //delete object to prevent memory leak
			source[i] = nullptr;
			v--;
			continue;
		} 
		dest[v] = source[i];
		source[i] = nullptr;
	}
}

int Hand::search(Card* c)
{
	for (int i = 0; i < num_of_cards; i++)
	{
		if (handptr[i] == c)
		{
			return i;
		}
	}
}

void Hand::add_card(Card* c)
{
	handptr[num_of_cards] = c;
	num_of_cards++;
}

void Hand::remove_card(int position)
{
	Card* copyptr[52] = {nullptr};
	copy(handptr, copyptr, position);
	copy(copyptr, handptr);
	num_of_cards--;
}

void Hand::remove_card(Card* c)
{
	int position = search(c);
	Card* copyptr[52] = { nullptr };
	copy(handptr, copyptr, position);
	copy(copyptr, handptr);
	num_of_cards--;
}

int Hand::getHand_Value()
{
	//handptr is the hand array
	int tval = 0;
	int acecount = 0;
	for (int c = 0; c < num_of_cards; c++)
	{
		tval += handptr[c]->getValue();
		if (handptr[c]->getDisplay() == Card::ACE)
		{
			acecount++;
		}
	}
	int modulodiff = (21 - tval) / 10;
	if (tval + 10*modulodiff <= 21 && acecount != 0)
	{
		tval += 10 * modulodiff;
	}
	return tval;
	// make it 21 unless it busts....

}

std::ostream& operator<<(std::ostream& stream, Hand h)
{
	for (int card_i = 0; card_i < h.getNumofcards(); card_i++)
	{
		stream << char(201);
		for (int w = 0; w < Card::CARD_WIDTH; w++)
		{
			stream << char(205);
		}
		stream << char(187);
	}
	stream << endl;
	//put the h
	for (int card_i = 0; card_i < h.getNumofcards(); card_i++)
	{
		Card* c = h.getHandptr()[card_i];
		if (c->getScreenDisplay() == "10" && !(c->getFaceup()))
		{
			stream << char(186) << c->getScreenDisplay() << ' ' << char(c->getSuit()) << setw(c->CARD_WIDTH - 3) << char(186);
		}
		else if (c->getFaceup())
		{
			stream << char(186);
			for (int w = 0; w < Card::CARD_WIDTH; w++)
			{
				stream << char(178);
			}
			stream << char(186);
		}
		else
		{
			stream << char(186) << c->getScreenDisplay() << ' ' << char(c->getSuit()) << setw(c->CARD_WIDTH - 2) << char(186);
		}
	}
	stream << endl;

	for (int he = 0; he < Card::CARD_HEIGHT - 1; he++)
	{
		for (int card_i = 0; card_i < h.getNumofcards(); card_i++)
		{
			if (h.getHandptr()[card_i]->getFaceup())
			{
				stream << char(186);
				for (int w = 0; w < Card::CARD_WIDTH; w++)
				{
					stream << char(178);
				}
				stream << char(186);
			}
			else
			{
				stream << char(186) << setw(Card::CARD_WIDTH + 1) << char(186);
			}
		}
		stream << endl;
	}
	for (int card_i = 0; card_i < h.getNumofcards(); card_i++)
	{
		Card* c = h.getHandptr()[card_i];
		if (c->getFaceup())
		{
			stream << char(186);
			for (int w = 0; w < Card::CARD_WIDTH; w++)
			{
				stream << char(178);
			}
			stream << char(186);
		}
		else
		{
			stream << char(186) << setw(c->CARD_WIDTH - 2) << c->getScreenDisplay() << ' ' << char(c->getSuit()) << char(186);
		}
	}
	stream << endl;

	for (int card_i = 0; card_i < h.getNumofcards(); card_i++)
	{
		stream << char(200);
		for (int w = 0; w < Card::CARD_WIDTH; w++)
		{
			stream << char(205);
		}
		stream << char(188);
	}
	stream << endl;
	

	return stream;
}