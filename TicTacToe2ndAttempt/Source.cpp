#include <iostream>
#include <string>
#include <vector>

void updateTileValue();
void drawBoard();
void AIMoves();
void mainMenu();
int getIntFromUser(int, int);
void playerMove();
void checkForWinsOrDraw();
bool exiting = false;
bool player2Exists = true;
bool player1Turn = true;
bool someoneWon = false;
std::string winner = "";


std::vector <std::vector <char>> board = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'} };
std::vector <std::vector <char>> originalBoard = {
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
		if (someoneWon == true) {
			std::cout << "The winner is: " << winner << "!\n";
			exiting = true;
			break;
		}
		if (player2Exists == true && player1Turn == false) {
			playerMove();
		}
		else if (player1Turn == true) {
			playerMove();
		}
		else if (player1Turn == false && player2Exists == false) {
			AIMoves();
		}
		updateTileValue();
		checkForWinsOrDraw();
		
		player1Turn = !player1Turn;
	}
	

	return 0;
}

void updateTileValue() {
	int lastEmptyRow;
	int lastEmptyCol;
	int counterX = 0;
	int counterO = 0;
	//Check if someone is 1 step from winning, in which case, either win or block it.
	//This checks horizontally
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (board[r][c] == 'O') {
				
				counterO++;
				//std::cout << r << c << "is O, counter == " << counterO << "\n";
			}
			else if (board[r][c] == 'X') {
				counterX++;
				//std::cout << r << c << "is X, counter == " << counterX << "\n";
			}
			else {
				lastEmptyRow = r;
				lastEmptyCol = c;
				//std::cout << r << c << "is empty\n";
			}

		}
		if ((counterX == 2 || counterO == 2) && (counterX + counterO) == 2) {
			//std::cout << "Horizontal Changing value " << tileValue[lastEmptyRow][lastEmptyCol] << "to ";
			tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
			//std::cout << tileValue[lastEmptyRow][lastEmptyCol] << "\n";
		}
		counterX = 0;
		counterO = 0;
	}
	//This one checks vertically
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (board[c][r] == 'O') {
				counterO++;
			}
			else if (board[c][r] == 'X') {
				counterX++;
			}
			else {
				lastEmptyRow = c;
				lastEmptyCol = r;
			}

		}
		if ((counterX == 2 || counterO == 2) && (counterX + counterO) == 2) {
			//std::cout << "Vertical Changing value " << tileValue[lastEmptyRow][lastEmptyCol] << "to ";
			tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
			//std::cout << tileValue[lastEmptyRow][lastEmptyCol] << "\n";
		}
		counterX = 0;
		counterO = 0;
	}

	for (int i = 0; i < board.size(); i++) {
		if (board[i][i] == 'O') {
			counterO++;
		}
		else if (board[i][i] == 'X') {
			counterX++;
		}
		else {
			lastEmptyRow = i;
			lastEmptyCol = i;

		}
		

	}
	if ((counterX == 2 || counterO == 2) && (counterX + counterO) == 2) {
		//std::cout << "Diagonal 1 Changing value " << tileValue[lastEmptyRow][lastEmptyCol] << "to ";
		tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
		//std::cout << tileValue[lastEmptyRow][lastEmptyCol] << "\n";
	}
	counterX = 0;
	counterO = 0;
	for (int i = 0; i < board.size(); i++) {
		if (board[(board.size() - 1) - i][i] == 'O') {
			counterO++;
		}
		else if (board[(board.size() - 1) - i][i] == 'X') {
			counterX++;
		}
		else {
			lastEmptyRow = (board.size() - 1) - i;
			lastEmptyCol = i;

		}
	}
	if ((counterX == 2 || counterO == 2) && (counterX+counterO) == 2) {
		//std::cout << "Diagonal 2 Changing value " << tileValue[lastEmptyRow][lastEmptyCol] << "to ";
		tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
		//std::cout << tileValue[lastEmptyRow][lastEmptyCol] << "\n";
	}
	counterX = 0;
	counterO = 0;
}

void checkForWinsOrDraw() {
	
	int pointsPlayer1 = 0;
	int pointsPlayer2 = 0;
	//Check for horizontal wins
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (board[r][c] == 'O') {
				pointsPlayer2++;
			}
			else if (board[r][c] == 'X') {
				pointsPlayer1++;
			}
			if (pointsPlayer1 == 3) {
				winner = "Player 1";
				someoneWon = true;
			}
			else if (pointsPlayer2 == 3) {
				winner = "Player 2";
				someoneWon = true;
			}
		}
		pointsPlayer1 = 0;
		pointsPlayer2 = 0;
	}
	//Check for vertical wins
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (board[c][r] == 'O') {
				pointsPlayer2++;
			}
			else if (board[c][r] == 'X') {
				pointsPlayer1++;
			}
			if (pointsPlayer1 == 3) {
				winner = "Player 1";
				someoneWon = true;
			}
			else if (pointsPlayer2 == 3) {
				winner = "Player 2";
				someoneWon = true;
			}
		}
		pointsPlayer1 = 0;
		pointsPlayer2 = 0;
	}
	//Check for diagonal wins
	for (int i = 0; i < board.size(); i++) {
		if (board[i][i] == 'O') {
			pointsPlayer2++;
		}
		else if (board[i][i] == 'X') {
			pointsPlayer1++;
		}
		if (pointsPlayer1 == 3) {
			winner = "Player 1";
			someoneWon = true;
		}
		else if (pointsPlayer2 == 3) {
			winner = "Player 2";
			someoneWon = true;
		}

	}
	pointsPlayer1 = 0;
	pointsPlayer2 = 0;
	for (int i = 0; i < board.size(); i++) {
		if (board[(board.size() - 1) - i][i] == 'O') {
			pointsPlayer2++;
		}
		else if (board[(board.size() - 1) - i][i] == 'X') {
			pointsPlayer1++;
		}
		if (pointsPlayer1 == 3) {
			winner = "Player 1";
			someoneWon = true;
		}
		else if (pointsPlayer2 == 3) {
			winner = "Player 2";
			someoneWon = true;
		}
	}
	pointsPlayer1 = 0;
	pointsPlayer2 = 0;
}

void AIMoves() {
	int destinationRow;
	int destinationCol;
	int targetValue = 0;
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (tileValue[r][c] > targetValue) {
				destinationCol = c;
				destinationRow = r;
				targetValue = tileValue[r][c];
				std::cout << "Highest value found so far at " << r << c << "\n";
			}
		}
	}

	board[destinationRow][destinationCol] = 'O';
	tileValue[destinationRow][destinationCol] = 0;
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
	tileValue[attemptRow][attemptCol] = 0;
	
	

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