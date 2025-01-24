#ifndef GAMEBOY_H
#define GAMEBOY_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "PlayerProfile.h"
#include "Menu.h"


class GameBoy {
public:
    GameBoy();
    void start(Game* game);
    void updateHighestScore(int score);
    //void displayGameOver(int score,SoundSystem& soundsystem);
    void displayGameOver(int score);

    void PlayerInput(sf::RenderWindow& window);
   // void resetData();
    sf::Font ArialFont;
    sf::Font TNRFont;

private:
    int highestScore;
    Player* player;
    Game* game;
    Menu menu;
};

#endif 
