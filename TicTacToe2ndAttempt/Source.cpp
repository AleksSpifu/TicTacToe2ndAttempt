#include <iostream>
#include <string>
#include <vector>

void drawBoard();
void AIMoves();
void mainMenu();
int getIntFromUser(int, int);
void playerMove();
bool exiting = false;
bool player2Exists = true;
bool player1Turn = true;


std::vector <std::vector <char>> board = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'} };
const std::vector <const std::vector <char>> originalBoard = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'} };
std::vector <std::vector <int>> tileValue = {
	{5, 3, 5},
	{3, 10, 3},
	{5, 3, 5} };


int main() {
	mainMenu();
	while (exiting == false) {
		drawBoard();
		if (player2Exists == true && player1Turn == false) {
			playerMove();
		}
		else if (player1Turn == true) {
			playerMove();
		}
		else if (player1Turn == false && player2Exists == false) {
			AIMoves();
		}
		
	}
	

	return 0;
}

void AIMoves() {


}

void playerMove() {
	char player;
	int attemptRow;
	int attemptCol;
	bool moveAccepted = false;
	int moveAttempt;
	while (moveAccepted == false) {
		moveAttempt = getIntFromUser(1, 9);
		if (moveAttempt > 6) {
			attemptRow = 2;
			attemptCol = moveAttempt - 7;
		}
		else if (moveAttempt <= 6 && moveAttempt > 3) {
			attemptRow = 1;
			attemptCol = moveAttempt - 4;
		}
		else if (moveAttempt <= 3 && moveAttempt > 0) {
			attemptRow = 0;
			attemptCol = moveAttempt - 1;
		}
		if (board[attemptRow][attemptCol] == originalBoard[attemptRow][attemptCol]) {
			moveAccepted = true;
		}
		else {
			std::cout << "Please choose a tile that's not already occupied.\n";
		}
	}
	if (player1Turn == true) {
		player = 'X';
	}
	else
	{
		player = 'O';
	}
	board[attemptRow][attemptCol] = player;
	player1Turn = !player1Turn;
	

}

void mainMenu() {
	system("cls");
	std::cout << "Please select gamemode:\n1. Play against AI and you start.\n2. Play against AI and the AI starts.\n3. Play with someone locally.\n4. Exit.\n";
	switch (getIntFromUser(1, 4))
	{
	case 1:
		player2Exists = false;
		player1Turn = true;
		break;
	case 2:
		player2Exists = false;
		player1Turn = false;
		break;
	case 3:
		player2Exists = true;
		player1Turn = true;
		break;
	case 4:
		exiting = true;
		break;
	default:
		break;
	}
}

void drawBoard() {
	
	//system("cls");
	for (int row = 0; row < board.size(); row++) {
		for (int col = 0; col < board[row].size(); col++) {
			std::cout << " | " << board[row][col];
		}
		std::cout << " | \n";
	}
	switch (player1Turn) {
	case true:
		std::cout << "It is X's turn to play.\n";
		break;
	case false:
		std::cout << "It is O's turn to play.\n";
		break;
	default:
		break;
	}
}

int getIntFromUser(int min, int max) {
	std::cout << "Please enter a number between " << min << " and " << max << ": \n";
	int userinput;
	std::cin >> userinput;
	while (userinput < min || userinput > max) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "Please enter a valid selection.\n";
		std::cin >> userinput;
	}
	return userinput;
}