#pragma once
#include "Hand.h"
class Deck : public Hand
{
public:
	Deck();
	Card* Draw(Hand* h);
};

