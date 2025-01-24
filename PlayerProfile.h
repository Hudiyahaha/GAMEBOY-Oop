#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& playerName, int playerScore);

    void setName(const std::string& playerName);
    void setScore(int playerScore);

    std::string getName() const;
    int getScore() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
