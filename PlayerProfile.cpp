#include "PlayerProfile.h"
using namespace std;

Player::Player(const string& playerName, int playerScore) : name(playerName), score(playerScore) {}

void Player::setName(const string& playerName) {
    name = playerName;
}

void Player::setScore(int playerScore) {
    score = playerScore;
}

string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::saveToFile(const string& filename) const {
   ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << name <<endl;
        outFile << score <<endl;
        outFile.close();
    } else {
       cerr << "Unable to open file for writing: " << filename <<endl;
    }
}

void Player::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        getline(inFile, name);
        inFile >> score;
        inFile.close();
    } else {
        cerr << "Unable to open file for reading: " << filename <<endl;
    }
}
