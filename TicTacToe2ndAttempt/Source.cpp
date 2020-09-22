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
bool draw = false;
std::string winner = "";


std::vector <std::vector <char>> board = { //This is what gets printed out and shown to the player.
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'} };
std::vector <std::vector <char>> originalBoard = { //This is so i can check wether or not a given tile has been taken or not. If "board" matches "originalBoard", i know the tile is empty.
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'} };
std::vector <std::vector <int>> tileValue = { //This is the priority system of the AI. Can be changed to suit different playstyles.
	{5, 3, 5},
	{3, 10, 3},
	{5, 3, 5} };


int main() {
	mainMenu(); //Ask if player 1 wants to play against AI or player 2, who starts and
	while (exiting == false) { //if the player chooses to exit in the menu, this will not happen.
		drawBoard(); //Print out the board
		if (someoneWon == true) { //These are pretty self-explanatory. They just exit if someone wins or if it's a draw.
			std::cout << "The winner is: " << winner << "!\n";
			exiting = true;
			break;
		} 
		else if (draw == true) {
			std::cout << "It's a draw!";
			exiting = true;
			break;
		}
		if (player2Exists == true && player1Turn == false) { //If it's player VS player and player 2 is up, a move from the player is required.
			playerMove(); //This will check whose turn it is.
		}
		else if (player1Turn == true) { //Else, regardless of wether or not it's against AI or Player, player 1 is always a player, and has to move
			playerMove();
		}
		else if (player1Turn == false && player2Exists == false) { //If it's player 2's turn and player 2 is the AI, call for the AI move function
			AIMoves();
		}
		updateTileValue(); //After this, the AI priority system will check for any piece with 2 in a row, and update the value of the remaining one to increase the chance of it being selected.
		checkForWinsOrDraw(); //also pretty self explanatory.
		
		player1Turn = !player1Turn; //Switch whose turn it is.
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
			}
			else if (board[r][c] == 'X') {
				counterX++;
			}
			else {
				lastEmptyRow = r;
				lastEmptyCol = c;
			}

		}
		if ((counterX == 2 || counterO == 2) && (counterX + counterO) == 2) {
			tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
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
			tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
		}
		counterX = 0;
		counterO = 0;
	}
	//The folowing two checks diagonally
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
		tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
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
		tileValue[lastEmptyRow][lastEmptyCol] = tileValue[lastEmptyRow][lastEmptyCol] * 10;
	}
	counterX = 0;
	counterO = 0;

	if (board[0][0] == 'X' && board[2][2] == originalBoard[2][2]) {
		tileValue[2][2] = tileValue[2][2] * 5;
	} 
	if (board[2][0] == 'X' && board[0][2] == originalBoard[0][2]) {
		tileValue[0][2] = tileValue[0][2] * 5;
	}
	if (board[2][2] == 'X' && board[0][0] == originalBoard[0][0]) {
		tileValue[0][0] = tileValue[0][0] * 5;
	}
	if (board[0][2] == 'X' && board[2][0] == originalBoard[2][0]) {
		tileValue[2][0] = tileValue[2][0] * 5;
	}
}

void checkForWinsOrDraw() {
	int counter = 0;
	int pointsPlayer1 = 0;
	int pointsPlayer2 = 0;
	//These check for 3 identical tiles in a row, and makes someonewon = true if thats the case.
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
	//if no one won, this checks all the tiles, and if all of them are taken, draw = true
	if (someoneWon == false) {
		for (int r = 0; r < board.size(); r++) {
			for (int c = 0; c < board[r].size(); c++) {
				if (board[r][c] != originalBoard[r][c]) {
					counter++;
				}
			}
		}
		if (counter == 9) {
			draw = true;
		}
	}
	
}

void AIMoves() {
	//This entire function simply searches from tile 1-9 and puts an O on the biggest value it finds. It will not switch if it finds an equal value,
	//so if all tiles are equal it will select 1, 2, 3, and so on. I don't need to check if the tile is occupied already, because when a tile is occupied,
	//it's value becomes 0, and instead of adding numbers to increase value, i use multiplication, so it will always stay 0,
	//so the AI will never select it. Unless ALL the tiles are 0, but then, either someone wins or it's a draw, so it's not an issue.
	int destinationRow;
	int destinationCol;
	int targetValue = 0;
	for (int r = 0; r < board.size(); r++) {
		for (int c = 0; c < board[r].size(); c++) {
			if (tileValue[r][c] > targetValue) {
				destinationCol = c;
				destinationRow = r;
				targetValue = tileValue[r][c];
			}
		}
	}

	board[destinationRow][destinationCol] = 'O';
	tileValue[destinationRow][destinationCol] = 0;
}

void playerMove() {
	//this function is pretty straight forward, it pretty much asks the currently active player to select a number, and checks if it's a valid move.
	char player;
	int attemptRow;
	int attemptCol;
	bool moveAccepted = false;
	int moveAttempt;
	while (moveAccepted == false) { //This will loop until the player enters a valid number.
		moveAttempt = getIntFromUser(1, 9); //ask for input, the function will make sure an integer between 1 and 9 is entered, but will not check
											//if the spot is taken. 
		//Here it turns the single number into a row and column, to be used below to check if the tile is occupied.
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
		//This is where the original board comes in handy, because if the tile is the same, that means it hasn't been used yet.
		if (board[attemptRow][attemptCol] == originalBoard[attemptRow][attemptCol]) {
			moveAccepted = true; //Accept the move and exit the while-loop
		}
		else { //Or ask again if it's not accepted.
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
	board[attemptRow][attemptCol] = player; //Replace the number with the correct letter.
	tileValue[attemptRow][attemptCol] = 0; //Set the value of the tile to 0 so the AI will not try to move to it.
	
	

}

void mainMenu() {
	//This function gets called when the program starts. it's pretty self-explanatory. 
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
	//This simply prints out the state of the board vector, and tells the player whose turn it is.
	//system("cls");
	std::cout << "\n";
	for (int row = 0; row < board.size(); row++) {
		std::cout << "\t";
		for (int col = 0; col < board[row].size(); col++) {
			std::cout << " | " << board[row][col];
		}
		std::cout << " | \n";
	}
	std::cout << "\n";
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
	//This is just an easier way to make sure only int values can be entered. there are probably better ways but this works for my purpose.
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