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
using namespace std;
using namespace sf;

Menu::Menu() {
    options[0] = "Hangman";
    options[1] = "Snake game";
    options[2] = "Wordle";
    options[3] = "Instructions";
    options[4] = "Leaderboard";
    options[5] = "Exit";
    selectedoption = 0;
}


int Menu::getoption() {
    return selectedoption;
}

void Menu::navigate(int direction) {
    selectedoption = (selectedoption + direction + 6) % 6;
}

string Menu::getOptionText(int index) {
    return options[index]; // Return the menu option text
}

void Menu::displayInstructionsScreen(RenderWindow& window, Font& ArialFont, Font& TNRFont) {
    Texture instructionTexture;
    if (!instructionTexture.loadFromFile("gamer3.jpg")) {
        cout << "Failed to load instruction2.png!" << endl;
        return;
    }
    Sprite instructionSprite(instructionTexture);

    /* Font font2;
     if (!ArialFont.loadFromFile("TNR.ttf")) {
         cout << "Failed to load Arial.ttf!" << endl;
         return;
     }*/

    Text backText("Press Enter to go back to the main menu.", TNRFont, 20);
    backText.setPosition(50, 350);
    backText.setFillColor(Color::Red);

    Text instructionsText("INSTRUCTIONS", TNRFont, 30);
    instructionsText.setPosition(50, 50);
    instructionsText.setStyle(Text::Bold | Text::Underlined);
    instructionsText.setFillColor(Color::Black);

    Text hangmanInstructions("Hangman: Guess the word by entering letters.", ArialFont, 20);
    hangmanInstructions.setPosition(50, 150);
    hangmanInstructions.setStyle(Text::Bold);
    hangmanInstructions.setFillColor(Color::Black);

    Text snakeInstructions("Snake: Use arrow keys to move the snake and eat food.", ArialFont, 20);
    snakeInstructions.setPosition(50, 200);
    snakeInstructions.setStyle(Text::Bold);
    snakeInstructions.setFillColor(Color::Black);

    Text wordleInstructions("Wordle: Guess the word in 6 tries.", ArialFont, 20);
    wordleInstructions.setPosition(50, 250);
    wordleInstructions.setStyle(Text::Bold);
    wordleInstructions.setFillColor(Color::Black);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                return; // Go back to the main menu
            }
        }
        window.clear();
        window.draw(instructionSprite);
        window.draw(instructionsText);
        window.draw(hangmanInstructions);
        window.draw(snakeInstructions);
        window.draw(wordleInstructions);
        window.draw(backText);
        window.display();
    }
}

void Menu::displayLeaderboardScreen(RenderWindow& window, Font& TNRFont) {
    Texture instructionTexture;
    if (!instructionTexture.loadFromFile("gamer3.jpg")) {
        cout << "Failed to load instruction2.png!" << endl;
        return;
    }
    Sprite instructionSprite(instructionTexture);


    Text backText("Press Enter to go back to the main menu.", TNRFont, 20);
    backText.setPosition(10, 600);
    backText.setFillColor(Color::Red);

    //Font font2;
    //if (!font.loadFromFile("TNR.ttf")) {
    //    cout << "Failed to load Arial.ttf!" << endl;
    //    return;
    //}

    Text leaderSprite("LEADERBOARD", TNRFont, 40);
    leaderSprite.setPosition(208, 30);
    leaderSprite.setFillColor(Color::Black);
    leaderSprite.setStyle(Text::Bold | Text::Underlined);

    LeaderBoard leaderboard;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                return; // Go back to the main menu
            }
        }

        window.clear();
        window.draw(instructionSprite);
        window.draw(leaderSprite);
        window.draw(backText);

        // Call the filedata method to display the leaderboard
        leaderboard.filedata(window, TNRFont);

        window.display();
    }
}

