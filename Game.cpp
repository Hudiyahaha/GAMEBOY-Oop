#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include "Game.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "GameBoy.h"
#include "Hangman.h"
#include "Snake.h"
using namespace std;
using namespace sf;

const int MAX_PLAYERS = 100; // Maximum number of players
int Game::score = 0;

void Game::increaseScoreBy30() {
    score += 30;
}

void Game::increaseScore() {
    Game::score += 10; // Use Game::score to reference the static member
}

int Game::getScore() {
    return Game::score; // Use Game::score to reference the static member
}

void Game::setScore(int newScore) {
    Game::score = newScore; // Set the static score
}

int Game::getHighestScore(const string& playerName) {
    ifstream inFile("scores.txt");
    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading: scores.txt" << endl;
        return 0;
    }

    string line;
    int highestScore = 0;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string name;
        int score;
        if (iss >> name >> score) {
            if (name == playerName && score > highestScore) {
                highestScore = score;
            }
        }
    }
    inFile.close();
    return highestScore;
}

void Game::saveScore(const string& playerName) {
    const int MAX_PLAYERS = 100;
    string names[MAX_PLAYERS];
    int scores[MAX_PLAYERS];
    int count = 0;

    // Read all scores into arrays
   ifstream inFile("scores.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line) && count < MAX_PLAYERS) {
           istringstream iss(line);
           string name;
            int score;
            if (iss >> name >> score) {
                names[count] = name;
                scores[count] = score;
                count++;
            }
        }
        inFile.close();
    }

    // Update the player's score if it's higher
    bool playerFound = false;
    for (int i = 0; i < count; ++i) {

        if (names[i] == playerName) {
            if (score > scores[i]) {
                scores[i] = score;
            }
            playerFound = true;
            break;
        }
    }

    // If the player was not found, add a new entry
    if (!playerFound && count < MAX_PLAYERS) {
        names[count] = playerName;
        scores[count] = score;
        count++;
    }

    // Write all scores back to the file
   ofstream outFile("scores.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < count; ++i) {
            outFile << names[i] << " " << scores[i] <<endl;
        }
        outFile.close();
    }
    else {
       cerr << "Unable to open file for writing: scores.txt" <<endl;
    }
}

