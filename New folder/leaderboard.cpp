/*
 * leaderboard.cpp
 *
 *  Created on: Apr 28, 2025
 *      Author: Mariam Samy
 */
#include "leaderboard.h"
#include "game_constants.h"
#include "game_logic.h"
#include <iostream>
#include <fstream>

#include <iomanip>
#include <map>
#include <vector>

using namespace std;

void Leaderboard::showLeaderboard() {
    GameLogic::clearScreen();
    cout << GOLD << BOLD << "\n\t" << trophy << " LEADERBOARD " << trophy << RESET << "\n\n";
    cout << " " << string(50, '=') << "\n";
    cout << " " << setw(20) << left << "PLAYER"
         << setw(10) << "WINS"
         << setw(10) << "LOSSES"
         << setw(10) << "DRAWS" << "\n";
    cout << " " << string(50, '=') << "\n";

    ifstream scoreFile("score.txt");
    if (!scoreFile) {
        cout << " No game records found.\n";
        return;
    }

    map<string, vector<int>> stats;
    string line;

    while (getline(scoreFile, line)) {
        if (line.empty()) continue;

        size_t pos1 = line.find('\t');
        size_t pos2 = line.find('\t', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        string player1 = line.substr(0, pos1);
        string player2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string result = line.substr(pos2 + 1);

        if (stats.find(player1) == stats.end()) stats[player1] = {0, 0, 0};
        if (stats.find(player2) == stats.end()) stats[player2] = {0, 0, 0};

        if (result == "DRAW") {
            stats[player1][2]++;
            stats[player2][2]++;
        } else {
            stats[result][0]++;
            string loser = (result == player1) ? player2 : player1;
            stats[loser][1]++;
        }
    }

    for (const auto& entry : stats) {
        cout << " " << setw(20) << left << entry.first << "  "
             << setw(10) << GREEN << entry.second[0] << RESET
             << setw(20) << RED << entry.second[1] << RESET
             << setw(20) << YELLOW << entry.second[2] << RESET
             << endl;
    }

    scoreFile.close();
    cout << " " << string(50, '=') << endl;
    cout << "\n " << star << " Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void Leaderboard::updateLeaderboard(const string &player1, const string &player2,
                                  const string &result) {
    ofstream scoreFile("score.txt", ios::app);
    scoreFile << player1 << "\t" << player2 << "\t" << result << "\n";
    scoreFile.close();
}



