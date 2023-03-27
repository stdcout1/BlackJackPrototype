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
	char play_again = 'y';
	while (play_again == 'y')
	{
		system("cls");
		Game* game = new Game();
		srand(time(0));
		game->PlayGame();
		delete game;
		cout << "Would you like to play a new game?";
		cin >> play_again;
	}
}