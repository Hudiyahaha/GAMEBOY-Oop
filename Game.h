#ifndef GAME_H
#define GAME_H

#include <iostream>
#include"LeaderBoard.h"
#include"SoundSystem.h"

class Game {
public:
    LeaderBoard* leaderBoard;
    static int score; // Static member variable for the score

    Game() {}
    virtual ~Game() {} // Virtual destructor for proper cleanup
    virtual void start() = 0;
    static void increaseScore();
    static int getScore();
    static void setScore(int newScore); // Add this method to set the score

    void saveScore(const std::string& playerName);
    void increaseScoreBy30();
    static int getHighestScore(const std::string& playerName); // Add this method to get the highest score for a player
};

#endif // GAME_H
