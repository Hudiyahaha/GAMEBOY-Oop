#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "GameBoy.h"
#include "Hangman.h"
#include "Snake.h"
#include "Game.h"
#include "WordleGame.h"
#include "LeaderBoard.h"
#include "PlayerProfile.h"
#include "Menu.h"
using namespace std;
using namespace sf;

void LeaderBoard::filedata(RenderWindow& window,Font& TNRFont) {
    Texture King;
    if (!King.loadFromFile("king.png")) {
      cerr << "Error loading king.png" << endl;
    }
    Sprite king_sprite;

    // Load leaderboard data from file
    const int MAX_PLAYERS = 100;
    string names[MAX_PLAYERS];
    int scores[MAX_PLAYERS];
    int count = 0;

  ifstream inFile("scores.txt");
    if (inFile.is_open()) {
     string line;
        while (getline(inFile, line) && count < MAX_PLAYERS) {
            istringstream iss(line);
            string name;
            int score;
            if (iss >> name >> score) {   //READing Data from File
                bool playerFound = false;
                for (int i = 0; i < count; ++i) {
                    if (names[i] == name) {
                        if (score > scores[i]) {
                            scores[i] = score;
                        }
                        playerFound = true;
                        break;
                    }
                }
                if (!playerFound) {
                    names[count] = name;
                    scores[count] = score;
                    count++;
                }
            }
        }
        inFile.close();
    }
    else {
     cerr << "Unable to open file for reading: scores.txt" <<endl;
        return;
    }

    // Sort leaderboard by scores in descending order
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) { // Swap if next score is greater
                //Swapping
                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

               string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;
            }
        }
    }

    // Display leaderboard items dynamically
    for (int i = 0; i < count; ++i) {
        // Player name
        Text playerText(names[i], TNRFont, 24);
        playerText.setPosition(200, 100 + i * 50);
        playerText.setFillColor(Color::Black);

        // Player score
       Text scoreText(to_string(scores[i]), TNRFont, 24);
        scoreText.setPosition(500, 100 + i * 50);
        scoreText.setFillColor(Color::Red);

        // Draw player name and score
        window.draw(playerText);
        window.draw(scoreText);

        // Display crown for top 3 players
        if (i < 3) {
            king_sprite.setTexture(King);
            king_sprite.setScale(0.01f, 0.01f); // Adjust the scale as needed
            king_sprite.setPosition(100, 100 + i * 50); // Position the crown above the player's name
            window.draw(king_sprite);

        }
    }
}
