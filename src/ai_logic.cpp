
#include "../include/ai_logic.h"
#include "../include/game_logic.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <thread>
#include "../include/game_constants.h"

using namespace std;

bool AILogic::isMoveValid(const vector<int>& used, int num) {
    return find(used.begin(), used.end(), num) == used.end();
}

void AILogic::easyAI(const vector<char>& board, vector<int>& used, int& choice) {
    cout << " " << dice << " Computer is choosing randomly...\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    choice = rand() % 9 + 1;
    while (!isMoveValid(used, choice)) {
        choice = rand() % 9 + 1;
    }
}

void AILogic::mediumAI(const vector<char>& board, vector<int>& used, int& choice,
                      char aiSymbol, char playerSymbol) {
    cout << " " << brain << " Computer is strategizing...\n";
    this_thread::sleep_for(chrono::milliseconds(500));

    // Check for winning move
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            vector<char> temp = board;
            temp[i] = aiSymbol;
            if (GameLogic::checkWin(temp) == 1) {
                choice = i + 1;
                return;
            }
        }
    }

    // Block opponent
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            vector<char> temp = board;
            temp[i] = playerSymbol;
            if (GameLogic::checkWin(temp) == 1) {
                choice = i + 1;
                return;
            }
        }
    }

    // Prefer center
    if (board[4] == '5') {
        choice = 5;
        return;
    }

    // Then corners
    vector<int> corners = {0, 2, 6, 8};
    for (int corner : corners) {
        if (board[corner] != 'X' && board[corner] != 'O') {
            choice = corner + 1;
            return;
        }
    }

    // Otherwise random move
    choice = rand() % 9 + 1;
    while (!isMoveValid(used, choice)) {
        choice = rand() % 9 + 1;
    }
}

int AILogic::minimax(vector<char> board, bool isMaximizing, char aiSymbol, char playerSymbol) {
    int result = GameLogic::checkWin(board);
    if (result == 1) return isMaximizing ? -10 : 10;
    if (result == 0) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                vector<char> temp = board;
                temp[i] = aiSymbol;
                int score = minimax(temp, false, aiSymbol, playerSymbol);
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                vector<char> temp = board;
                temp[i] = playerSymbol;
                int score = minimax(temp, true, aiSymbol, playerSymbol);
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

void AILogic::hardAI(const vector<char>& board, vector<int>& used, int& choice, char aiSymbol) {
    cout << " " << genius << " Computer is calculating perfect move...\n";
    this_thread::sleep_for(chrono::milliseconds(500));

    int bestScore = -1000;
    int bestMove = -1;
    char playerSymbol = (aiSymbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            vector<char> temp = board;
            temp[i] = aiSymbol;
            int score = minimax(temp, false, aiSymbol, playerSymbol);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    choice = bestMove + 1;
}


