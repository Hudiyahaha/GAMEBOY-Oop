#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "WordleGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include"SoundSystem.h"
using namespace std;
using namespace sf;

string WordleGame::randword() {
    srand(time(nullptr));    //getting random word from dictionary
    int random = rand() % 100;
    return Dictionary.getlist(random);
}

string WordDictionary::getlist(int index) {
    return list[index];
}
void drawKeyboard(RenderWindow& window, RectangleShape keys[3][10], Text keyLabels[3][10]) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 10; col++) {
			window.draw(keys[row][col]);  //drawing each key
			window.draw(keyLabels[row][col]); //drawing corresponding text on each key
		}
	}
}
//initializing the main grid  of wordle
void initializeGrid(RectangleShape** grid, int rows, int cols, float squareSize, float spacing) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool draw = false;
            grid[i][j].setSize(Vector2f(squareSize, squareSize));
            grid[i][j].setPosition(j * (squareSize + spacing) + 250, i * (squareSize + spacing) + 100);
            grid[i][j].setFillColor(Color::White);
        }
    }
}

void WordleGame::start() {
    const int rows = 6;              // number of rows (attempts)
    const int cols = 5;              // number of columns (letters per word)
    const float squaresize = 70;      
    const float spacing = 10;          
    WordleGame game;
    string origword = game.randword();  //generating a random word
    cout << origword << endl;
  //dyanmic grid for wordle
    RectangleShape** grid = new RectangleShape * [rows];
    for (int i = 0; i < rows; i++) {
        grid[i] = new RectangleShape[cols];
    }
   
 
    initializeGrid(grid, rows, cols, squaresize, spacing);
    RenderWindow window(VideoMode(950, 800), "Wordle Game");
   
    Texture texture;
    if (!texture.loadFromFile("wbg.jpg")) {
        std::cout << "failed to load wbg.jpg!" << endl;
        return;
    }
    Sprite sprite(texture);
    //setting up keyboard
	string keyboard[3] = { "QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM" };
	RectangleShape keys[3][10]; //squares for the keyboard
    int count = 0;
	Text keyLabels[3][10];//letter on the keys
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "failed to load arial.ttf!" << endl;
        return;
    }
	int keyWidth = 60, keyHeight = 60;
    float startX[3] = { 150.0f, 180.0f, 240.0f };  
	float startY = 600;
    //initializing keyboard and its labels
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < keyboard[row].size(); col++) {
			keys[row][col].setSize(Vector2f((float)keyWidth, (float)keyHeight));
			keys[row][col].setPosition(startX[row] + col * (keyWidth + spacing), startY + row * (keyHeight + spacing));
			keys[row][col].setFillColor(Color::White);
            count++;
			keys[row][col].setOutlineColor(Color::Black);
			keys[row][col].setOutlineThickness(2);

			// Setting up the text for each key
            count++;
			keyLabels[row][col].setFont(font);
			keyLabels[row][col].setString(string(1, keyboard[row][col]));
			keyLabels[row][col].setCharacterSize(24);
			keyLabels[row][col].setFillColor(Color::Black);

			// Centering the text within the key
            count++;
			float keyPosX = keys[row][col].getPosition().x;
			float keyPosY = keys[row][col].getPosition().y;

			keyLabels[row][col].setPosition(
				keyPosX + keyWidth / 4, // Horizontal centering

				keyPosY + keyHeight / 4 // Vertical centering 
			);
            count++;
		}
	}

    bool matched[rows][cols] = { false }; //matrix to track if the letters have matched
    Text welcometext("Wordle", font, 70);
    welcometext.setPosition(330, 10);
    welcometext.setFillColor(Color::White);
    welcometext.setStyle(Text::Bold | Text::Underlined);

    Text pausedText("Game Paused. Press 'Esc' to resume.", font, 30);
    pausedText.setPosition(50, 400);
    pausedText.setFillColor(Color::Blue);

    Text textt("GAME OVER Press Enter to restart ", font, 20);
    textt.setPosition(520, 10);
    textt.setFillColor(Color::White);

    Text inputtext("", font, 50);
    inputtext.setPosition(100, 660);
    inputtext.setFillColor(Color::Green);

    Text WonText("You Won! Press Enter to restart", font, 25);
    WonText.setPosition(520, 10);
    WonText.setFillColor(Color::White);

    Text scoreText("Score: ", font, 30);
    scoreText.setString("Score: " + to_string(game.getScore())); // Update score display

    scoreText.setPosition(10, 10);
    scoreText.setFillColor(Color::White);

    Text scoreText2("Score: ", font, 30);
    scoreText2.setString("Score: " + to_string(game.getScore())); // Update score display
    scoreText2.setPosition(50, 400);
    scoreText2.setFillColor(Color::Green);

    Text exitingText("Exiting Wordle", font, 30);
    exitingText.setPosition(50, 500);
    exitingText.setFillColor(Color::Red);

    SoundSystem back("wordleback.mp3",true);
    back.playBackgroundMusic();

    SoundSystem music2("gameover2.wav",false);
    SoundSystem music3("wordle win.wav", false);
    string* guessedwords = new string[rows];
    for (int i = 0; i < rows; i++) {  //initializing guessed words
        guessedwords[i] = "";  
    }

    bool won = false;
   
    int rowcount = 0;  //keeping track of number of guesses made 
    bool gameover = false;
    bool paused = false;
    int** keyStates = new int* [3];    //array to guess the state of each key
    for (int i = 0; i < 3; i++) {
        keyStates[i] = new int[10]();  // Each row has 10 integers, initialized to zero
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    paused = !paused;  //pause when esc is pressed
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
                    window.clear(sf::Color::White);
                    window.draw(exitingText);
                    scoreText2.setString("Score: " + std::to_string(Game::getScore()));
                    window.draw(scoreText2);
                    window.display();
                    sf::sleep(sf::seconds(2)); 
                    back.stopBackgroundMusic();
                    window.close();
                    return; // Exiting to the main menu
                }

                if ((gameover || won) && event.key.code == sf::Keyboard::Enter) {
                    //reseting the game state
                    rowcount = 0;
                    count = 0;
                    gameover = false;
                    won = false;
                    origword = game.randword(); //generating a new word
                   // cout << origword << endl;

                    // Clearing guessed words and matched grid
                    for (int i = 0; i < rows; i++) {
                        guessedwords[i] = "";
                        for (int j = 0; j < cols; j++) {
                            grid[i][j].setFillColor(Color::White);
                            matched[i][j] = false;
                        }
                    }
                      for (int i = 0; i < rows; i++) {
                        guessedwords[i] = "";
                        for (int j = 0; j < cols; j++) {
                            grid[i][j].setFillColor(Color::White);
                            matched[i][j] = false;
                        }
                    }
                      //clearing keyboard from the previous game
                      for (int row = 0; row < 3; row++) {
                          for (int col = 0; col < 10; col++) {
                              keys[row][col].setFillColor(Color::White);
                              keyStates[row][col] = 0; 
                          }
                      }
                }
            }
             if (event.type == Event::TextEntered) {
                char pressedKey = static_cast<char>(toupper(event.text.unicode));
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < keyboard[row].size(); col++) {
                        if (keyboard[row][col] == pressedKey) {
                            count++;
                            keys[row][col].setFillColor(Color::Green);
                            keyStates[row][col] = 1; // Mark as "correct" (green)
                        }
                    }
                }
            }
            if (event.type == Event::TextEntered && !gameover && !paused) {
                char letter = static_cast<char>(event.text.unicode);
                if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') && guessedwords[rowcount].length() < cols) {
                    guessedwords[rowcount] += letter;
                }
                if (event.key.code == Keyboard::BackSpace && !guessedwords[rowcount].empty()) {
                    guessedwords[rowcount].resize(guessedwords[rowcount].size() - 1);
                }
                //updating game coors based on correct and incorrect guesses
                if (guessedwords[rowcount].length() == cols) {
                    bool correct = true;
                    count--;
                    for (int i = 0; i < cols; i++) {
                        if (guessedwords[rowcount][i] == origword[i] && !matched[rowcount][i]) {
                            grid[rowcount][i].setFillColor(Color::Green);  //correct letter in position
                            matched[rowcount][i] = true;
                        }
                        else {
                            correct = false;
                            count++;
                            bool found = false;
                            for (int j = 0; j < cols; j++) {
                                if (guessedwords[rowcount][i] == origword[j] && i != j && !matched[rowcount][j]) {
                                    found = true;
                                    break;
                                }
                            }
                            if (found && !matched[rowcount][i]) {
                                grid[rowcount][i].setFillColor(Color::Yellow); //correct letter in wrong position
                            }
                        }
                    }
                    if (correct) {  //if the word entered is correct
                        won = true;
                        gameover = true;
                        count = 0;
                        Game::increaseScore(); // Increase score by 10 points
                        scoreText.setString("Score: " + std::to_string(Game::getScore())); // Updating score text
                    }
                    else if (rowcount == rows - 1) {
                        gameover = true;// if the limit is reached game over
                    }
                    else {
                        rowcount++;//move to next row
                    }
                }
            }
        }

        window.clear();
        window.draw(sprite);
        //drawing the grid
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                window.draw(grid[i][j]);
            }
        }
        //drawing input letter on the grid
        for (int row = 0; row <= rowcount; row++) {
            for (int i = 0; i < guessedwords[row].length(); i++) {
                Text lettertext(string(1, guessedwords[row][i]), font, 50);
                lettertext.setPosition(i * (squaresize + spacing) + 250, row * (squaresize + spacing) + 100);
                lettertext.setFillColor(Color::Black);
                count++;
                window.draw(lettertext);
            }
        }

        window.draw(welcometext);
        window.draw(scoreText); // Drawing the score

        if (paused) {
            window.clear(sf::Color::White);
            window.draw(pausedText);  
            //back.stopBackgroundMusic();
        }
        if (gameover) {
            if (won) {
                //window.clear(sf::Color::Blue);
                music3.playBackgroundMusic();
                window.draw(WonText);

            }
            else {
                //window.clear(sf::Color::Blue);
                music2.playBackgroundMusic();
                window.draw(textt);
            }
        }
		drawKeyboard(window, keys, keyLabels);
        window.display();
    }
    for (int i = 0; i < rows; i++) {
        delete[] grid[i];
    }

    delete[] grid;
    for (int i = 0; i < 3; i++) {
        delete[] keyStates[i];  
    }
    delete[] keyStates;
}
