#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <typeinfo>
#include <fstream>
using namespace std;
int score = 0;
bool exit_in_game = false;

struct draye // for every single cell of gameboard
{
	int amount;
	int x;
	int y;
	bool is_do;	  // for check to add the draye only ones
	bool is_fool; // to check the existence of a number is draye
};

struct Player // saving players and cout them in leader board
{
	string name;
	int score;
};

Player *Sort_Player(Player *players, int count) // thats for sorting score players
{
	for (int i = 0; i < count - 1; i++)
	{
		if (players[i].score < players[i + 1].score)
		{
			swap(players[i].name, players[i + 1].name);
			swap(players[i].score, players[i + 1].score);
			i = -1;
		}
	}
	return players;
}

bool check_win(draye **game_board, int size) // for checking that we are win or not
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (game_board[i][j].amount == 2048)
			{
				return true;
			}
		}
	}
	return false;
}

bool check_loose(draye **game_board, int size) // for checking that we are loose or not
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (game_board[i][j].amount == 0)
			{
				return true;
			}
			if (game_board[i][j].amount == game_board[i + 1][j].amount)
			{
				return true;
			}
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (game_board[i][j].amount == 0)
			{
				return true;
			}
			if (game_board[i][j].amount == game_board[i][j + 1].amount)
			{
				return true;
			}
		}
	}
	if (game_board[size - 1][size - 1].amount == 0)
		return true;
	return false;
}

draye **move(draye **game_board, int size, bool &is_change) // in this function we do all about moving number in game board .
{

	char usertInput = getch();
	is_change = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			game_board[i][j].is_do = false;
		}
	}

	switch (usertInput)
	{
	case 'd': // for click right
		for (int i = 0; i < size; i++)
		{
			for (int j = size - 2; j >= 0; j--)
			{
				if (game_board[i][j].is_fool == true) // movement in down direction
				{
					if (game_board[i][j + 1].is_fool == false)
					{
						swap(game_board[i][j + 1].amount, game_board[i][j].amount);
						swap(game_board[i][j + 1].is_fool, game_board[i][j].is_fool);
						i = 0;
						j = size-1;
						is_change = true;
					}
				}
				if (game_board[i][j + 1].amount == game_board[i][j].amount) // add tow nummber in down direction
				{
					if (game_board[i][j].is_fool == true and game_board[i][j + 1].is_fool == true)
					{
						if (!game_board[i][j].is_do and !game_board[i][j + 1].is_do)
						{
							game_board[i][j].is_fool = false;
							game_board[i][j].amount = 0;
							game_board[i][j + 1].is_do = true;
							game_board[i][j + 1].amount *= 2;
							score += game_board[i][j + 1].amount * 2;
							i = 0;
							j = size-1;
							is_change = true;							
						}
					}
				}
			}
		}
		break;

	case 'a': // for click left
		for (int i = 0; i < size; i++)
		{
			for (int j = 1; j < size; j++)
			{
				if (game_board[i][j].is_fool == true) // to movement left in tanle
				{
					if (game_board[i][j - 1].is_fool == false)
					{
						swap(game_board[i][j - 1].amount, game_board[i][j].amount);
						swap(game_board[i][j - 1].is_fool, game_board[i][j].is_fool);
						i = 0;
						j = 0;
						is_change = true;
					}
				}
				if (game_board[i][j - 1].amount == game_board[i][j].amount) // add tow number in left direction
				{
					if (game_board[i][j].is_fool == true and game_board[i][j - 1].is_fool == true)
					{
						if (!game_board[i][j].is_do and !game_board[i][j - 1].is_do)
						{
							game_board[i][j].amount = 0;
							game_board[i][j].is_fool = false;
							score += game_board[i][j - 1].amount * 2;
							game_board[i][j - 1].amount *= 2;
							game_board[i][j - 1].is_do = true;
							i = 0;
							j = 0;
							is_change = true;
						}
					}
				}
			}
		}
		break;

	case 'w': // for click up
		for (int i = 1; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (game_board[i][j].is_fool == true) // movement up in table
				{
					if (game_board[i - 1][j].is_fool == false)
					{
						swap(game_board[i - 1][j].amount, game_board[i][j].amount);
						swap(game_board[i - 1][j].is_fool, game_board[i][j].is_fool);
						i = 1;
						j = -1;
						is_change = true;
					}
				}
				if (game_board[i - 1][j].amount == game_board[i][j].amount) // add to number in uo direction
				{
					if (game_board[i][j].is_fool == true and game_board[i - 1][j].is_fool == true)
					{
						if (!game_board[i][j].is_do and !game_board[i - 1][j].is_do)
						{

							game_board[i][j].amount = 0;
							game_board[i][j].is_fool = false;
							score += game_board[i - 1][j].amount * 2;
							game_board[i - 1][j].amount *= 2;
							game_board[i - 1][j].is_do = true;
							i = 1;
							j = -1;
							is_change = true;
						}
					}
				}
			}
		}
		break;

	case 's': // for click down
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (game_board[i][j].is_fool == true) // for movement down in table
				{
					if (game_board[i + 1][j].is_fool == false)
					{
						swap(game_board[i + 1][j].amount, game_board[i][j].amount);
						swap(game_board[i + 1][j].is_fool, game_board[i][j].is_fool);
						i = 0;
						j = 0;
						is_change = true;
					}
				}
				if (game_board[i + 1][j].amount == game_board[i][j].amount) // add tow in down direction
				{
					if (game_board[i][j].is_fool == true and game_board[i + 1][j].is_fool == true)
					{
						if (!game_board[i][j].is_do and !game_board[i + 1][j].is_do)
						{
							game_board[i][j].amount = 0;
							game_board[i][j].is_fool = false;
							score += game_board[i + 1][j].amount * 2;
							game_board[i + 1][j].amount *= 2;
							game_board[i + 1][j].is_do = true;
							i = 0;
							j = 0;
							is_change = true;
						}
					}
				}
			}
		}
		break;
	case 'u':
	{
		break;
	}
	case 'e':
		exit_in_game = true;
	}
	return game_board;
}

void print_number_with_coler(int number) // in this function we print numbers with backgrand color in gameboard
{
	if (number == 2)
	{
		cout << "\033[40;1m   2    \033[0m";
	}
	else if (number == 0)
	{
		cout << "        ";
	}
	else if (number == 4)
	{
		cout << setw(5) << "\033[41;1m   4    \033[0m";
	}
	else if (number == 8)
	{
		cout << setw(5) << "\033[42;1m   8    \033[0m";
	}
	else if (number == 16)
	{
		cout << setw(5) << "\033[43;1m   16   \033[0m";
	}
	else if (number == 32)
	{
		cout << setw(5) << "\033[44;1m   32   \033[0m";
	}
	else if (number == 64)
	{
		cout << setw(5) << "\033[45;1m   64   \033[0m";
	}
	else if (number == 128)
	{
		cout << setw(5) << "\033[46;1m   128  \033[0m";
	}
	else if (number == 256)
	{
		cout << setw(5) << "\033[47;1m   256  \033[0m";
	}
	else if (number == 512)
	{
		cout << setw(5) << "\033[40;1m   512  \033[0m";
	}
	else if (number == 1024)
	{
		cout << setw(5) << "\033[41;1m  1024  \033[0m";
	}
	if (number == 2048)
	{
		cout << setw(5) << "\033[42;1m  2048  \033[0m";
	}
}

void print_game_board(draye **game_board, int size) // for print the game board and table
{
	system("cls");
	for (int i = 0; i < size; i++)
	{

		cout << "                                                            ";
		for (int j = 0; j < +size * 9 + 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					cout << "\u2554";
					continue;
				}
				else if (j == size * 9)
				{
					cout << "\u2557";
					continue;
				}
				else if (j % 9 == 0)
				{
					cout << "\u2566";
					continue;
				}
				else
				{
					cout << "\u2550";
					continue;
				}
			}
			else if (i == size - 1)
			{
				if (j == 0)
				{
					cout << "\u2560";
					continue;
				}
				else if (j == size * 9)
				{
					cout << "\u2563";
					continue;
				}
				else if (j % 9 == 0)
				{
					cout << "\u256C";
					continue;
				}
				else
				{
					cout << "\u2550";
					continue;
				}
			}
			else
			{
				if (j == 0)
				{
					cout << "\u2560";
					continue;
				}
				else if (j == size * 9)
				{
					cout << "\u2563";
				}
				else if (j % 9 == 0)
				{
					cout << "\u256C";
					continue;
				}
				else
				{
					cout << "\u2550";
					continue;
				}
			}
		}
		cout << endl;
		cout << "                                                            ";
		cout << "\u2551";
		for (int j = 0; j < size; j++)
		{
			print_number_with_coler(game_board[i][j].amount);
			cout << "\u2551";
		}
		cout << endl;
	}
	cout << "                                                            ";
	for (int j = 0; j < +size * 9 + 1; j++)
	{
		if (j == 0)
		{
			cout << "\u255A";
			continue;
		}
		else if (j == size * 9)
		{
			cout << "\u255D";
			continue;
		}
		else if (j % 9 == 0)
		{
			cout << "\u2569";
			continue;
		}
		else
		{
			cout << "\u2550";
			continue;
		}
	}
	cout << endl;
	cout << "                                                                      your score is : " << score << endl;
	cout << "-----------------------" << endl;
}

draye **Random_deraye(draye **game_board, int size, bool is_change) // for getting random number in game board
{
	draye a;

	if (is_change)
	{
		bool there_is_empty_amount = false;
		for (int i = 0; i < size; i++) // existance of empty draye
		{
			for (int j = 0; j < size; j++)
			{
				if (game_board[i][j].is_fool == false)
				{
					there_is_empty_amount = true;
					break;
				}
			}
			if (there_is_empty_amount == true)
			{
				break;
			}
		}
		if (there_is_empty_amount)
		{
			do
			{
				a.x = rand() % size;
				a.y = rand() % size;
			} while (game_board[a.x][a.y].is_fool == true);
			if (rand() % 4 != 0) // the chanse of number
			{
				a.amount = 2;
			}
			else
			{
				a.amount = 4;
			}
			a.is_fool = true;
			game_board[a.x][a.y] = a;
			return game_board;
		}
		return game_board;
	}
	return game_board;
}

void save_leaderboard(string name) // saving score and name of players in file 
{
	ofstream outputFile("Leaderboard.txt", ios::app); // write informations of players in file
	if (outputFile.is_open())
	{

		outputFile << name << "," << score << endl;
		outputFile.close();
	}
	else
	{
		cout << "Failed to open the file." << endl;
	}
}

void Leader_board() // show the sorted saved information 
{
	Player *players = new Player[100];
	ifstream file("Leaderboard.txt");
	if (file.is_open())
	{
		string line;
		int count = 0;
		while (getline(file, line)) // reading informations aboat players .
		{
			Player player;
			player.name = line.substr(0, line.find(','));
			player.score = stoi(line.substr(line.find(",") + 1, line.length() - (line.find(",") + 1)));
			players[count] = player;
			count++;
		}
		players = Sort_Player(players, count); // sort players
		for (int i = 0; i < count; i++)
		{
			cout << "                                                             "
				 << "(" << i + 1 << ")" << setw(15) << players[i].name << setw(10) << players[i].score << endl;
		}
		count = 0;
		getch();
		system("cls");
		file.close();
	}
	else
	{
		cerr << "Unable to open the file." << endl;
	}
}

void New_Game() // for creating a new game
{
	srand(static_cast<unsigned int>(time(nullptr)));
	bool is_change = true; // for check the change of game board
	string name;		   // for saving them in file
	int size;
	cout << "enter your name : ";
	cin >> name;
	while (true) // for getting correct value for size
	{
		cout << "Enter the size(between 2 to 18) of your table you want to play with " << endl
			 << " (if your is biggar then 13 please maximize your game screen ) : ";
		cin >> size;
		if (size < 2 || size > 18)
		{
			cout << "invalid value " << endl;
			Sleep(1000);
		}
		else
		{
			break;
		}
	}
	draye **game_board = new draye *[size];
	for (int i = 0; i < size; i++)
	{
		game_board[i] = new draye[size];
	}
	for (int i = 0; i < size; i++) // creat gameboard
	{
		for (int j = 0; j < size; j++)
		{
			game_board[i][j].amount = 0;
			game_board[i][j].is_fool = false;
		}
	}
	game_board = Random_deraye(game_board, size, is_change);
	while (true) // for begining the game
	{
		game_board = Random_deraye(game_board, size, is_change);
		is_change = false;
		print_game_board(game_board, size);
		if (!check_loose(game_board, size)) // Loose
		{
			cout << " game over " << endl;
			Sleep(3000);
			save_leaderboard(name);
			score = 0;
			system("cls");
			return;
		}
		if (check_win(game_board, size)) // Win
		{
			cout << "winnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn" << endl;
			Sleep(3000);
			score = 0;
			save_leaderboard(name);
			system("cls");
			return;
		}
		if (exit_in_game)
		{
			exit_in_game = false;
			system("cls");
			return;
		}
		game_board = move(game_board, size, is_change);
	}
	for (int i = 0; i < size; i++)
	{
		delete game_board[i];
	}
	delete game_board;
}

void menu() // MENU
{
	Sleep(500);
	cout << "                                                   if you want to go and PLAY our beautifull game press 1" << endl
		 << endl;
	Sleep(500);
	cout << "                                                      if you want to check the LEADER BOARD press 2 " << endl
		 << endl;
	Sleep(500);
	cout << "                                                             and if you want to EXIT press 3" << endl
		 << endl;
}

int main()
{
	cout << "                                        ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗   \n";
	cout << "                                        ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗  \n";
	cout << "                                        ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║  \n";
	cout << "                                        ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║  \n";
	cout << "                                        ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝  \n";
	cout << "                                         ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝   \n";
	cout << "                                                                                                                              \n";
	cout << "                                                            ██████╗  ██████╗ ██╗  ██╗ █████╗                                  \n";
	cout << "                                                            ╚════██╗██╔═████╗██║  ██║██╔══██╗                                 \n";
	cout << "                                                             █████╔╝██║██╔██║███████║╚█████╔╝                                 \n";
	cout << "                                                            ██╔═══╝ ████╔╝██║╚════██║██╔══██╗                                 \n";
	cout << "                                                            ███████╗╚██████╔╝     ██║╚█████╔╝                                 \n";
	cout << "                                                            ╚══════╝ ╚═════╝      ╚═╝ ╚════╝                                  \n";
	char need;

	while (true) // for begin the game and menu
	{
		menu();

		need = getch();
		switch (need)
		{
		case '1':
			New_Game();
			break;
		case '2':
			system("cls");
			Leader_board();
			break;
		case '3':

			return 0;
			break;
		default:
			cout << "                                                                    invalid value" << endl;
			Sleep(1000);
			system("cls");
			break;
		}
	}
}
