#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "GameBoy.h"
#include "Hangman.h"
#include "Snake.h"
#include "Game.h"
#include "WordleGame.h"
#include <sstream>
#include "LeaderBoard.h"
#include "PlayerProfile.h"
#include "Menu.h"
using namespace std;
using namespace sf;

GameBoy::GameBoy() : highestScore(0), player(nullptr), game(nullptr) 
{
        if (!ArialFont.loadFromFile("Arial.ttf")) {
            cout << "Failed to load TNR.ttf!" << endl;
        }
        if (!TNRFont.loadFromFile("TNR.ttf")) {
            cout << "Failed to load Arial.ttf!" << endl;
        }
}

void GameBoy::updateHighestScore(int score) {
    if (score > highestScore) {
        highestScore = score;
    }
}

void GameBoy::displayGameOver(int score) {
    cout << "Game Over! Your score: " << score << endl;
    updateHighestScore(score);
    cout << "Highest score: " << highestScore << endl;
    if (player) {
        game->saveScore(player->getName());
    }
}

void GameBoy::PlayerInput(RenderWindow& window) {
    string playerName;
    /*Font font;
    if (!font.loadFromFile("TNR.ttf")) {
        cout << "Failed to load Arial.ttf!" << endl;
        return;
    }*/
   

    Texture InputTexture;
    InputTexture.loadFromFile("namer.jpg");
    Sprite InputSprite(InputTexture);

    Text inputText("Enter your name: ", TNRFont, 32);
    inputText.setPosition(50, 50);
    inputText.setFillColor(Color::Black);
    //inputText.setStyle(Text::Bold);

    Text playerNameText("", TNRFont, 28);
    playerNameText.setPosition(50, 100);
    playerNameText.setFillColor(Color::Black);
   // inputText.setStyle(Text::Bold);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                }
                else if (event.text.unicode == '\r') { // Handle enter
                    player = new Player(playerName, 0); // Initialize player with name and score 0
                    player->saveToFile("player.txt"); // Save player information to file
                    return;
                }
                else if (event.text.unicode < 128) { // Handle regular character input
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
        }

        playerNameText.setString(playerName);

        window.clear(Color::White);
        window.draw(InputSprite);
        window.draw(inputText);
        window.draw(playerNameText);
        window.display();
    }
}

void GameBoy::start(Game* game) {
    RenderWindow window(VideoMode(800, 800), "Main Menu");

    // Load and play background music
    SoundSystem backgroundMusic("menu.mp3",true);
    backgroundMusic.playBackgroundMusic();

    
    PlayerInput(window); // Call PlayerInput to get the player's name

   Texture texture;
    if (!texture.loadFromFile("nintendo.jpg")) {
       cout << "Failed to load nintendo.jpg!" << endl;
        return;
    }
    Sprite sprite(texture);

    /*Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        cout << "Failed to load Arial.ttf!" << endl;
        return;


    }*/
    Text welcomeText("Welcome to the GAME BOY!", TNRFont, 30);
    welcomeText.setPosition(50, 50);
  //  welcomeText.setStyle(Text::Bold);
    welcomeText.setFillColor(Color::Magenta);

    Text welcomeText2("Which game do you want to play?", TNRFont, 20);
    welcomeText2.setPosition(50, 100);
    welcomeText2.setFillColor(Color::Magenta);

    /*Font font2;
    if (!font.loadFromFile("TNR.ttf")) {
        cout << "Failed to load Arial.ttf!" << endl;
        return;
    }*/

    Text menuText; // Single Text object for rendering
    menuText.setFont(TNRFont);
    menuText.setCharacterSize(25);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Handle key presses for navigation
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    menu.navigate(-1); // Move up in the menu
                }
                else if (event.key.code == Keyboard::Down) {
                    menu.navigate(1); // Move down in the menu
                }
                else if (event.key.code == Keyboard::Enter) {
                    int selectedGame = menu.getoption();
                    if (selectedGame == 0 || selectedGame == 1 || selectedGame == 2) {
                        backgroundMusic.stopBackgroundMusic(); // Stop the music when starting a game
                    }
                    if (selectedGame == 0) {
                        game = new Hangman();
                        game->start();
                        displayGameOver(game->getScore());
                    }
                    else if (selectedGame == 1) {
                        game = new Snake();
                        game->start();
                        displayGameOver(game->getScore());
                    }
                    else if (selectedGame == 2) {
                        game = new WordleGame();
                        game->start();
                        displayGameOver(game->getScore());
                    }
                    else if (selectedGame == 3) {
                        menu.displayInstructionsScreen(window,ArialFont,TNRFont);
                    }
                    else if (selectedGame == 4) {
                        menu.displayLeaderboardScreen(window,TNRFont);
                    }
                    else if (selectedGame == 5) {
                        cout << "Exiting" << endl;
                        return;
                    }
                }
            }
        }

        // Clear the window
        window.clear();
        backgroundMusic.resumeBackgroundMusic();
        // Draw the background and welcome text
        window.draw(sprite);
        window.draw(welcomeText);
        window.draw(welcomeText2);

        // Render the menu options
        for (int i = 0; i < 6; i++) {
            menuText.setString(menu.getOptionText(i));   // Set the text for the current option
            menuText.setPosition(100, 200 + i * 50);    // Position each option dynamically

            // Highlight the currently selected option
            if (i == menu.getoption())
                menuText.setFillColor(Color::Yellow);
            else
                menuText.setFillColor(Color::White);  // Default color

            window.draw(menuText); // Draw the current menu option
        }

       
        window.display();
    }
}

int main() {
    Game* game = nullptr;
    GameBoy gameBoy;

    gameBoy.start(game);

    return 0;
}
