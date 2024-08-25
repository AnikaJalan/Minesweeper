#include <bits/stdc++.h>
using namespace std;

int SIDE;
int MINES;
int BEGINNER=0;
int INTERMEDIATE=1;
int ADVANCED=2;
int MAXSIDE=25;
int MAXMINES=99;
int MAXSIZE=526;

bool isValid(int row, int col) {
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

class Board {
public:
    char** board;
    Board() {
        board = new char*[MAXSIDE + 1];
        for (int i = 0; i <= MAXSIDE; i++) {
            board[i] = new char[MAXSIDE + 1];
            for (int j = 0; j <= MAXSIDE; j++) {
                board[i][j] = '-';
            }
        }
    }

    bool isMine(int row, int col) {
        if (board[row][col] == '*')
            return (true);
        else
            return (false);
    }

    void makeMove(int* x, int* y) {
        cout << "Enter your move, (row, column) -> ";
        cin >> *x >> *y;
        return;
    }

    void printBoard() {
        int i, j;
        cout << "    ";

        for (i = 0; i < SIDE; i++)
            cout << i << " ";

        cout << "\n\n";

        for (i = 0; i < SIDE; i++) {
            cout << i << "   ";

            for (j = 0; j < SIDE; j++)
                cout << board[i][j] << " ";
            cout << "\n";
        }
        return;
    }

    int countAdjacentMines(int row, int col, int mines[][2]) {
        int i;
        int count = 0;

        int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for (int d = 0; d < 8; d++) {
            int newRow = row + dx[d];
            int newCol = col + dy[d];

            if (isValid(newRow, newCol)) {
                if (isMine(newRow, newCol))
                    count++;
            }
        }
        return (count);
    }

    void placeMines(int mines[][2]) {
        bool mark[MAXSIDE * MAXSIDE];
        memset(mark, false, sizeof(mark));

        for (int i = 0; i < MINES;) {
            int random = rand() % (SIDE * SIDE);
            int x = random / SIDE;
            int y = random % SIDE;

            if (!mark[random]) {
                mines[i][0] = x;
                mines[i][1] = y;

                board[mines[i][0]][mines[i][1]] = '*';
                mark[random] = true;
                i++;
            }
        }
        return;
    }

    void replaceMine(int row, int col) {
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] != '*') {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
        }
        return;
    }
};

class Game {
public:
    bool playMinesweeperUtil(Board& myBoard, Board& realBoard, int mines[][2], int row, int col, int* movesLeft) {
        if (myBoard.board[row][col] != '-')
            return (false);

        int i, j;

        if (realBoard.board[row][col] == '*') {
            myBoard.board[row][col] = '*';
            for (i = 0; i < MINES; i++)
                myBoard.board[mines[i][0]][mines[i][1]] = '*';

            myBoard.printBoard();
            cout << "\nYou lost!\n";
            return (true);
        } else {
            int count = realBoard.countAdjacentMines(row, col, mines);
            (*movesLeft)--;

            myBoard.board[row][col] = count + '0';

            if (!count) {
                int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

                for (int d = 0; d < 8; d++) {
                    int newRow = row + dx[d];
                    int newCol = col + dy[d];

                    if (isValid(newRow, newCol)) {
                        if (!realBoard.isMine(newRow, newCol))
                            playMinesweeperUtil(myBoard, realBoard, mines, newRow, newCol, movesLeft);
                    }
                }
            }
            return (false);
        }
    }

    void cheatMinesweeper(Board& realBoard) {
        cout << "The mines locations are-\n";
        realBoard.printBoard();
        return;
    }

    void playMinesweeper(Board& realBoard, Board& myBoard) {
        bool gameOver = false;
        int movesLeft = SIDE * SIDE - MINES, x, y;
        int mines[MAXMINES][2];

        realBoard.placeMines(mines);
        int currentMoveIndex = 0;

        while (!gameOver) {
            cout << "Current Status of Board : \n";
            myBoard.printBoard();
            myBoard.makeMove(&x, &y);

            if (currentMoveIndex == 0) {
                if (realBoard.isMine(x, y))
                    realBoard.replaceMine(x, y);
            }

            currentMoveIndex++;
            gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);

            if (!gameOver && (movesLeft == 0)) {
                cout << "\nYou won !\n";
                gameOver = true;
            }
        }
        return;
    }
};

void chooseDifficultyLevel() {

    int level;
	cout<<"Enter the Difficulty of the game:"<<endl;
	cout<<"Press 0 for beginer level."<<endl;  // 9x9;
	cout<<"Press 1 for intermediate level."<<endl;  //16x16
	cout<<"Press 2 for hard level."<<endl;  // 24x24

    cin >> level;

    if (level == BEGINNER) {
        SIDE = 9;
        MINES = 10;
    }

    if (level == INTERMEDIATE) {
        SIDE = 16;
        MINES = 40;
    }

    if (level == ADVANCED) {
        SIDE = 24;
        MINES = 99;
    }
}

int main() {
    Board myBoard, realBoard;
    Game* game = new Game();
    chooseDifficultyLevel();
    game->playMinesweeper(myBoard, realBoard);
    return 0;
}
