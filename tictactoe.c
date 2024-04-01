/*
Title: 2-Player Tic-Tac-Toe
Author: Samuel Li
Date: March 31, 2024
*/

#include <stdio.h>
#include <stdlib.h>

char board[3][3]; // 3x3 board
char instruction[2]; // current instruction from user

char myGetChar(); // read the next character from standard input, and check for EOF.
void resetBoard(); // reset board
void displayBoard(); // display board
void displayInstructions(); // display instructions
int win(); // check board for a win/draw

int isNumber(char c); // return true if c is a digit, false otherwise
void end(); // terminate program

int clearLine(int c); // remove current line from standard input and return 0
int readInstruction(); // attempt to read the current instruction into instruction[]
                       // return true if a valid instruction was entered
void getInstruction(int gameInProgress); // get a valid instruction from the user
                                         // by calling readInstruction repeatedly

void startGame(); // begin a tic-tac-toe game

char myGetChar() {
    char c = getchar();
    if (c == EOF) {
        printf("End-of-file detected. Exiting.\n");
        exit(0);
    }
    return c;
}

void resetBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard() {
    printf("\n-------------\n");
    for (int i = 0; i < 3; ++i) {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        printf("-------------\n");
    }
    printf("\n");
}

void displayInstructions() {
    printf("\nINSTRUCTIONS\n");
    printf("------------------------------------------------------------------------------\n");
    printf("h: help (redisplay instructions)\n");
    printf("r: exit current game to main menu / start new game\n");
    printf("q: quit\n\n");
    printf("To make a move during a game, enter two numbers separated by a single space.\n");
    printf("The numbers must be between 0 and 2, and they represent the coordinates\n");
    printf("of the square the current player wishes to mark.\n");
    printf("(0 0) represents the top left corner, (0 2) represents the top right,\n");
    printf("(2 0) represents the bottom left, and (2 2) represents the bottom right.\n");
    printf("Parentheses are NOT required for the above instructions.\n");
    printf("All instructions must be entered by pressing ENTER.\n\n");
    printf("------------------------------------------------------------------------------\n\n");
}

// return 0 if board is not in a win state
// return 1 if player 1 won
// return 2 if player 2 won
// return 3 if draw
int win() {
    for (int i = 0; i <= 2; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] != ' ') return (board[i][0] == 'X') ? 1 : 2;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] != ' ') return (board[0][i] == 'X') ? 1 : 2;
        }
    }
    
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] != ' ') return (board[0][0] == 'X') ? 1 : 2;
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
        if (board[2][0] != ' ') return (board[2][0] == 'X') ? 1 : 2;
    }

    int ret = 3;
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j] == ' ') ret = 0;
        }
    }
    
    return ret;
    
}

int isNumber(char c) {
    return 0 <= 'c' && 'c' <= '9';
}

void end() {
    printf("Thank you for playing!\n");
    exit(0);
}

int clearLine(int c) {
    if (c == '\n') return 0;
    for (c = myGetChar(); c != '\n'; c = myGetChar()) {

    }
    return 0;
}

// updates global variable instruction
// return true if successful
// a valid instruction is either "x y" where
// x and y are between 0 and 2, or one of
// 'r', 'q', 'h'
// a newline must follow the instruction
int readInstruction() {
    int c = myGetChar();

    if (c >= '0' && c <= '2') {

        instruction[0] = c;
        c = myGetChar();
        if (c != ' ') return clearLine(c);

        c = myGetChar();
        if (c >= '0' && c <= '2') {
            instruction[1] = c;
            c = myGetChar();
            if (c != '\n') return clearLine(c);
            return 1;
        }
        if (c != '\n') return clearLine(c);
    }

    if ((c == 'r' || c == 'q') || c == 'h') {
        instruction[0] = c;
        c = myGetChar();
        if (c == '\n') return 1;
        return clearLine(c);
    }

    return clearLine(c);

}

void getInstruction(int gameInProgress) {
    while (1) {
        if (!readInstruction()) {
            printf("Invalid instruction. Try again: \n");
            continue;
        }

        if (!gameInProgress && isNumber(instruction[0])) {
            printf("Invalid instruction; the game has not started. Try again: \n");
            continue;
        }

        break;
    }
}

void startGame() {

    resetBoard();
    displayBoard();
    int player = 1;

    while (!win()) {
        printf("Player %d, enter a command: ", player);
        getInstruction(1);

        char instr = instruction[0];
        if (instr == 'q') end();
        if (instr == 'h') {
            displayInstructions();
            continue;
        }
        if (instr == 'r') {
            printf("Ending game and returning to menu.\n");
            return;
        }

        int first = instruction[0] - '0';
        int second = instruction[1] - '0';
        if (board[first][second] != ' ') {
            printf("That square is taken. Try again.\n");
            continue;
        }
        board[first][second] = (player == 1) ? 'X' : 'O';
        printf("\n");
        displayBoard();
        player = (player == 1) ? 2 : 1;
    }

    int w = win();
    if (w == 1) {
        printf("Player 1 wins!\n");
    } else if (w == 2) {
        printf("Player 2 wins!\n");
    } else {
        printf("Draw.\n");
    }
    printf("Current game has ended. Returning to main menu.\n\n");
}

int main() {
    printf("Welcome to 2-Player Tic-Tac-Toe by Samuel Li!\n");
    displayInstructions();

    while (1) {
        printf("Press r to start game or q to quit.\n");
        getInstruction(0);
        char instr = instruction[0];
        if (instr == 'q') end();
        if (instr == 'h') displayInstructions();
        if (instr == 'r') startGame();
    }
    
    return 0;

}
