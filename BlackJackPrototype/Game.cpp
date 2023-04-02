#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;



Game::Game()
{
	bal = 0;
	betammount = 0;

	fstream scoresfile("blackjackscores.txt");
	if (scoresfile.is_open())
	{
		scoresfile >> bal;
		scoresfile.close();
	}
	else {
		scoresfile.close();
		bal = 100;
		ofstream _("blackjackscores.txt");
		_ << bal;
		_.close();
	}
	cout << "Your current balance is: $" << bal << endl;
}

Game::~Game()
{
	ofstream scoresfilev2("blackjackscores.txt", ios::trunc);
	scoresfilev2 << bal;
	scoresfilev2.close();
}
void Game::show(Hand* ph, Hand* dh)
{
	system("cls");
	cout << "Dealers Cards" << endl;
	cout << *dh << endl;
	cout << "Player Hands" << endl;
	cout << *ph << endl;
}



char Game::ask()
{
	cout << "Hit or stand: ";
	char choice;
	cin >> choice;
	return choice;
}


Game::move_returns Game::move(bool stand, Hand* ph, Hand* dh, Deck* d) // PLAYERBUST if you cant move after last move...
{
	if (stand)
	{
		//if standing do dealer logic
		dh->getHandptr()[0]->setFaceup(false);
		d->Draw(dh);
		show(ph, dh);
		if (dh->getHand_Value() > 16)
		{
			return DELEAR16;
		}
		else if (dh->getHand_Value() > 21)
		{
			return DEALERBUST;
		}
		else
		{
			return OK;
		}
	}
	else
	{
		//hit logic for player
		d->Draw(ph);
		show(ph, dh);
		return ph->getHand_Value() > 21 ? PLAYERBUST : OK;
	}

}


void Game::resultofgame() {


	double multiplier = 0;
	if (gamestate > 3 )
	{
		multiplier = 1.5;
	}
	else
	{
		multiplier = -1;

	}
	bal = bal + (multiplier * betammount);

	switch (int(gamestate))
	{
	case 0:

		cout << "Instant loss by dealer\n";
		cout << "Your new balance is " << bal << endl;

		break;
	case 1:
		cout << "Loss by dealer\n";
		cout << "Your new balance is " << bal << endl;

		break;
	case 2:
		cout << "You have gone over 21, you loss\n";
		cout << "Your new balance is " << bal << endl;

		break;
	case 3:
		cout << "The dealer has busted you win!\n";
		cout << "Your new balance is " << bal << endl;

		break;
	case 4:
		cout << "Your cards are closest to 21!, you win\n";
		cout << "Your new balance is " << bal << endl;

		break;
	case 5:
		cout << "You got blackjack!, you win\n";
		cout << "Your new balance is " << bal << endl;
		break;
	case 6:
		cout << "insufficient funds.";
		break;
	default:
		break;
	}

	//Win
	if (gamestate > 3) {
		cout << "\nYOU WIN!\n";
		system("Color 60");
		system("Color 60");
		system("Color 60");
		system("Color E0");
		system("Color E0");
		system("Color E0");
		system("Color 90");
		system("Color 90");
		system("Color 90");
		system("Color 10");
		system("Color 10");
		system("Color 10");
		system("Color 90");
		system("Color 90");
		system("Color 90");
		system("Color B0");
		system("Color B0");
		system("Color B0");
		system("Color 30");
		system("Color 30");
		system("Color 30");
		system("Color B0");
		system("Color B0");
		system("Color B0");
		system("Color D0");
		system("Color D0");
		system("Color D0");
		system("Color 50");
		system("Color 50");
		system("Color 50");
	}
	//Lose
	else {
		cout << "\nYou lose. Better luck next time!\n";
		system("Color F0");
		system("Color F0");
		system("Color 70");
		system("Color 70");
		system("Color C0");
		system("Color C0");
		system("Color 40");
		system("Color 40");
	}

}

void Game::PlayGame()
{
	Deck* deck = new Deck();
	Hand* phand = new Hand();
	Hand* dhand = new Hand();


	cout << "Welcome to the game!" << endl;
	cout << "Enter an ammount to bet: ";
	cin >> betammount;
	if (bal - betammount < 0)
	{
		gamestate = NOT_ENOUGH_MONEY;
		cout << "Error: Invalid funds." << endl; 
		cout << "Enter 'y' to start a new game and enter an amount wihtin your balance range." << endl; 
		//resultofgame();
		return;
	}
	cout << "The dealer has:" << endl;
	deck->Draw(dhand);
	deck->Draw(dhand);
	dhand->getHandptr()[0]->setFaceup(true);
	cout << *dhand;
	cout << dhand->getHand_Value() << endl;
	cout << "You have: " << endl;
	deck->Draw(phand);
	deck->Draw(phand);
	cout << *phand;
	cout << phand->getHand_Value() << endl;
	//preflip bj check
	if (phand->getHand_Value() == 21)
	{
		dhand->getHandptr()[0]->setFaceup(false);
		show(phand, dhand);
		gamestate =  INSTANT_WIN;
		resultofgame();
		return;
	}
	else if (dhand->getHand_Value() == 21)
	{
		dhand->getHandptr()[0]->setFaceup(false);
		show(phand, dhand);
		gamestate = INSTANT_LOSS;
		resultofgame();
		return;
	}

	bool stand = false;
	move_returns cont = OK;
	char choice = 's';
	while (cont == OK)
	{
		if (!stand)
		{
			cout << "Hit or stand (please input h for hit and s for stand): ";
			cin >> choice;
		}
		switch (choice)
		{
			case int('h') :
				cont = move(false, phand, dhand, deck);
				break;
				case int('s') :
					cont = move(true, phand, dhand, deck);
					stand = true;
					break;
				default:
					cout << "Invalid command" << endl;
					break;
		}
	}
	//after this line no more cards are added

	if (cont == DEALERBUST)
	{
		gamestate = WINBYBUST;
	}
	else if (cont == PLAYERBUST)
	{
		gamestate = LOSSBYBUST;
	}
	else // this is if dealer16
	{

		if (dhand->getHand_Value() > 21)
		{
			gamestate = WINBYSELF;
		}
		else if (dhand->getHand_Value() > phand->getHand_Value())
		{
			gamestate = LOSSBYDEALER;
		}
		else
		{
			gamestate = WINBYSELF;
		}
	}
	resultofgame();
};

