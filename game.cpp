#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <fstream>

using namespace std;

#define MAX_NAME_LENGTH 50
#define LEADERBOARD_SIZE 5
#define FILENAME "leaderboard.txt"

struct Player {
    char name[MAX_NAME_LENGTH];
    int guesses;
};

void ClearInputBuffer() {
    int c;
    while ((c = cin.get()) != '\n' && c != EOF);
}

void DisplayLeaderboard(Player leaderboard[]) {
    cout << "\n--- Leaderboard ---\n";
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (leaderboard[i].guesses > 0) {
            cout << leaderboard[i].name << " made " << leaderboard[i].guesses << " guess" << (leaderboard[i].guesses > 1 ? "es" : "") << endl;
        }
    }
}

void UpdateLeaderboard(Player leaderboard[], const char* name, int guesses) {
    int playerIndex = -1;

    // Check if the player already exists in the leaderboard
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (strcmp(name, leaderboard[i].name) == 0) {
            playerIndex = i;
            break;
        }
    }

    if (playerIndex != -1) {
        // Player exists, update their score if it's better
        if (guesses < leaderboard[playerIndex].guesses) {
            leaderboard[playerIndex].guesses = guesses;
        }
    }
    else {
        // Player doesn't exist, find the lowest score and replace if necessary
        int lowestIndex = 0;
        for (int i = 1; i < LEADERBOARD_SIZE; i++) {
            if (leaderboard[i].guesses < leaderboard[lowestIndex].guesses) {
                lowestIndex = i;
            }
        }

        // Replace the lowest score with the new player's score
        if (guesses < leaderboard[lowestIndex].guesses) {
            strncpy(leaderboard[lowestIndex].name, name, MAX_NAME_LENGTH);
            leaderboard[lowestIndex].guesses = guesses;
        }
    }
}

void SaveLeaderboard(Player leaderboard[]) {
    ofstream file(FILENAME);
    if (!file) {
        cerr << "Error opening " << FILENAME << " for writing." << endl;
        return;
    }

    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        file << leaderboard[i].name << " " << leaderboard[i].guesses << "\n";
    }
}

void LoadLeaderboard(Player leaderboard[]) {
    ifstream file(FILENAME);
    if (!file) {
        cout << "No existing leaderboard found." << endl;
        return;
    }

    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (file >> leaderboard[i].name >> leaderboard[i].guesses) {
            // Successfully read a line from the file
        }
        else {
            cerr << "Error reading leaderboard data." << endl;
            break;
        }
    }
}

int GetGuess(int numrand) {
    int numguess;
    cin >> numguess;
    ClearInputBuffer();

    if (numguess > numrand) {
        cout << "Too high, guess again: ";
    }
    else if (numguess < numrand) {
        cout << "Too low, guess again: ";
    }

    return numguess;
}

int PlayGuessingGame(Player leaderboard[]) {
    srand(time(nullptr));
    int numrand = (rand() % (100 - 10 + 1)) + 10;

    double sqrtnum = sqrt(static_cast<double>(numrand));

    cout << sqrtnum << " is the square root of what number?" << endl;

    int numguess;
    int attempts = 0;

    while (true) {
        numguess = GetGuess(numrand);
        attempts++;

        if (numguess == numrand) {
            cout << "You got it, baby!" << endl;
            return attempts;
        }
    }
}

int main() {
    Player leaderboard[LEADERBOARD_SIZE];
    char name[MAX_NAME_LENGTH];
    char c;

    cout << "Welcome! Press 'q' to quit or any other key to continue:" << endl;

    LoadLeaderboard(leaderboard);

    while (true) {
        cout << "Please enter your name to start: ";
        cin.getline(name, sizeof(name));
        int attempts = PlayGuessingGame(leaderboard);

        cout << "You made " << attempts << " guess" << (attempts > 1 ? "es" : "") << "." << endl;

        UpdateLeaderboard(leaderboard, name, attempts);
        DisplayLeaderboard(leaderboard);
        SaveLeaderboard(leaderboard);

        cout << "Press 'q' to quit or any other key to continue:" << endl;
        cin >> c;
        ClearInputBuffer();

        if (c == 'q') {
            cout << "Bye Bye!" << endl;
            break;
        }
    }

    return 0;
}
