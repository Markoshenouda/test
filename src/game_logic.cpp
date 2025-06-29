
#include "../include/game_logic.h"
#include "../include/game_constants.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#define OS "nt"
#else
#define OS "posix"
#endif

using namespace std;

void GameLogic::clearScreen() {
    if (OS == "nt") system("cls");
    else system("clear");
    cout << PURPLE << BOLD << "\n\t" << star << " ULTIMATE TIC-TAC-TOE " << star << RESET << "\n";
}

void GameLogic::wait(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void GameLogic::displayColorfulBoard(char x, char o, const string &u1,
                                   const string &u2, const vector<char> &board) {
    clearScreen();

    // Player headers with icons
    cout << "\n " << person << " " << PINK << BOLD << u1 << RESET << " (" << (x == 'X' ? crossIcon : circleIcon) << ")\n";
    cout << " " << (u2 == "Computer" ? robot : person) << " " << CYAN << BOLD << u2 << RESET << " (" << (o == 'X' ? crossIcon : circleIcon) << ")\n\n";

    // Top border
    cout << "   " << cornerTL << horizontalLine << cornerTR << "\n";

    for (int i = 0; i < 9; i += 3) {
        cout << "   " << verticalLine;
        for (int j = i; j < i + 3; ++j) {
            char ch = board[j];
            if (ch == 'X') cout << " " << RED << BOLD << crossIcon << RESET << " " << verticalLine;
            else if (ch == 'O') cout << " " << BLUE << BOLD << circleIcon << RESET << " " << verticalLine;
            else cout << "  " << YELLOW << ch << "  " << verticalLine;
        }
        cout << "\n";

        if (i < 6) cout << "   " << tee << horizontalLine << "\n";
    }

    // Bottom border
    cout << "   " << cornerBL << horizontalLine << cornerBR << "\n\n";
}

int GameLogic::checkWin(const vector<char> &board) {
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (const auto &combo : winCombos) {
        if (board[combo[0]] == board[combo[1]] && board[combo[1]] == board[combo[2]]) {
            return 1;
        }
    }

    for (char c : board) {
        if (c != 'X' && c != 'O') {
            return -1;
        }
    }

    return 0;
}



