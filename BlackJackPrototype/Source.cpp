#include <iostream>
#include <fstream>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "Game.h"
#include <stdio.h>
using namespace std;




int main()
{
	system("color 20");
	Game* game = new Game();
	srand(time(0));
	game->PlayGame();
	delete game;
	
}