#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 8; // Board size
const int MINES = 10; // Number of mines

vector<vector<char>> board(SIZE, vector<char>(SIZE, '.'));
vector<vector<char>> displayBoard(SIZE, vector<char>(SIZE, '#'));
vector<vector<bool>> revealed(SIZE, vector<bool>(SIZE, false));

void placeMines() {
    srand(time(0));
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (board[x][y] != 'M') {
            board[x][y] = 'M';
            count++;
        }
    }
}

int countMines(int x, int y) {
    int mines = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == 'M') {
                mines++;
            }
        }
    }
    return mines;
}

void initializeBoard() {
    placeMines();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'M') {
                board[i][j] = '0' + countMines(i, j);
            }
        }
    }
}

void printBoard() {
    cout << "  ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << displayBoard[i][j] << " ";
        }
        cout << endl;
    }
}

void reveal(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || revealed[x][y]) return;
    revealed[x][y] = true;
    displayBoard[x][y] = board[x][y];
    if (board[x][y] == '0') {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                reveal(x + dx, y + dy);
            }
        }
    }
}

bool isWin() {
    int covered = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!revealed[i][j] && board[i][j] != 'M') {
                covered++;
            }
        }
    }
    return covered == 0;
}

int main() {
    initializeBoard();
    while (true) {
        printBoard();
        int x, y;
        cout << "Enter coordinates (row and column): ";
        cin >> x >> y;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Invalid coordinates! Try again.\n";
            continue;
        }
        if (board[x][y] == 'M') {
            cout << "Game Over! You hit a mine.\n";
            break;
        }
        reveal(x, y);
        if (isWin()) {
            cout << "Congratulations! You cleared the board!\n";
            break;
        }
    }
    return 0;
}
