#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;



Game::Game()
{
	d = new Deck();
	ph = new Hand();
	dh = new Hand();

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
	cout << bal;

}

Game::~Game()
{
	ofstream scoresfilev2("blackjackscores.txt", ios::trunc);
	scoresfilev2 << bal;
	scoresfilev2.close();
}
void Game::show()
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


Game::move_returns Game::move(move_options move) // PLAYERBUST if you cant move after last move...
{
	if (move == STAND)
	{
		//if standing do dealer logic
		dh->getHandptr()[0]->setFaceup(false);
		
		show();
		if (dh->getHand_Value() >= 16)
		{
			return DELEAR16;
		}
		else if (dh->getHand_Value() > 21)
		{
			return DEALERBUST;
		}
		else
		{
			d->Draw(dh);
			return OK;
		}
	}
	else if (move == HIT)
	{
		//hit logic for player
		d->Draw(ph);
		show();
		return ph->getHand_Value() > 21 ? PLAYERBUST : OK;
	}

	else if (move == DOUBLEDOWN)
	{
		if (ph->getNumofcards() == 2)
		{
			d->Draw(ph);
			show();
			return ph->getHand_Value() > 21 ? PLAYERBUST : DOUBLEDOWNRETURN;
		}
		else
		{
			dh->getHandptr()[0]->setFaceup(false);

			show();
			if (dh->getHand_Value() >= 16)
			{
				return DELEAR16;
			}
			else if (dh->getHand_Value() > 21)
			{
				return DEALERBUST;
			}
			else
			{
				d->Draw(dh);
				return OK;
			}
		}
	}

}


void Game::resultofgame() {


	double multiplier = 0;
	if (gamestate > 3 && gamestate == 6)
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
		system("Color E0");
		system("Color A0");
		system("Color 20");
		system("Color A0");
		system("Color 90");
		system("Color 10");
		system("Color 90");
		system("Color B0");
		system("Color 30");
		system("Color B0");
		system("Color D0");
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
	cout << "Welome to the game" << endl;
	cout << "Enter ammount to bet: ";
	cin >> betammount;
	if (bal - betammount < 0 || betammount < 0)
	{
		gamestate = NOT_ENOUGH_MONEY;
		resultofgame();
		return;
	}
	cout << "The dealer has:" << endl;
	d->Draw(dh);
	d->Draw(dh);
	dh->getHandptr()[0]->setFaceup(true);
	cout << *dh;
	cout << dh->getHand_Value() << endl;
	cout << "You have: " << endl;
	d->Draw(ph);
	d->Draw(ph);
	cout << *ph;
	cout << ph->getHand_Value() << endl;
	//preflip bj check
	if (ph->getHand_Value() == 21)
	{
		dh->getHandptr()[0]->setFaceup(false);
		show();
		gamestate =  INSTANT_WIN;
		resultofgame();
		return;
	}
	else if (dh->getHand_Value() == 21)
	{
		dh->getHandptr()[0]->setFaceup(false);
		show();
		gamestate = INSTANT_LOSS;
		resultofgame();
		return;
	}

	bool stand = false;
	move_returns cont = OK;
	char choice = 's';
	move_returns temp = OK;
	while (cont == OK)
	{
		if (!stand)
		{
			cout << "Hit, stand or double down: ";
			cin >> choice;
		}
		switch (choice)
		{
			case int('h') :
				cont = move(HIT);
				break;
			case int('s') :
				cont = move(STAND);
				stand = true;
				break;
			case int('d') :
				cont = move(DOUBLEDOWN);
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
	else // this is if dealer16 or double down
	{

		if (dh->getHand_Value() > 21)
		{
			gamestate = WINBYSELF;
		}
		else if (dh->getHand_Value() > ph->getHand_Value())
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

