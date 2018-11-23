#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <stdlib.h> 

using namespace std;

vector<vector<int>> rows, cols, boxes;

bool fill(vector<vector<char>> &board, int x, int y)
{
    // fill all lines
    if (y == 9)
        return true;

    int nx = (x + 1) % 9;
    int ny = (nx == 0) ? y + 1 : y;

    for (int i = 1; i < 10; i++)
    {
        if (!rows[y][i] && !cols[x][i] && !boxes[(y / 3) * 3 + (x / 3)][i])
        {
            rows[y][i] = 1;
            cols[x][i] = 1;
            boxes[(y / 3) * 3 + (x / 3)][i] = 1;
            board[y][x] = i + '0';
            if (fill(board, nx, ny))
                return true;
            board[y][x] = '.';
            rows[y][i] = 0;
            cols[x][i] = 0;
            boxes[(y / 3) * 3 + (x / 3)][i] = 0;
        }
    }
    return false;
}

void solveSuduko(vector<vector<char>> &board)
{
    rows = vector<vector<int>>(9, vector<int>(10));
    cols = vector<vector<int>>(9, vector<int>(10));
    boxes = vector<vector<int>>(9, vector<int>(10));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            const char c = board[i][j];
            if (c != '.')
            {
                int n = c - '0';
                rows[i][n] = 1;
                cols[j][n] = 1;
                boxes[(i / 3) * 3 + (j / 3)][n] = 1;
            }
        }
    }

    fill(board, 0, 1);
}

vector<vector<char>> init()
{
    vector<vector<char>> board;

    rows = vector<vector<int>>(9, vector<int>(10));
    cols = vector<vector<int>>(9, vector<int>(10));
    boxes = vector<vector<int>>(9, vector<int>(10));

    srand(unsigned(time(0)));
    vector<char> tmp;
    for (int i = 1; i < 10; i++)
        tmp.push_back('0' + i);
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(tmp.begin(), tmp.end(), default_random_engine(seed));

    board.push_back(tmp);

    vector<char> tmp2(9, '.');

    for (int i = 0; i < 8; i++) board.push_back(tmp2);

    solveSuduko(board);

    return board;
}

void print(const vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void generateSudoku(vector<vector<char>> &board, int d)
{
    int difficulty = d * 20;
    while (difficulty--)
    {
        board[rand() % 9][rand() % 9] = '.';
    }
}

int main()
{
    cout << "Set difficulty (Easy - 1/Medium - 2/Hard - 3):" << endl;
    int d = 0;
    cin >> d;
    vector<vector<char>> board = init();
    generateSudoku(board, d);
    print(board);
}