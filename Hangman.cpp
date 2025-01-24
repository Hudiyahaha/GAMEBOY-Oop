#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Hangman.h"
#include "Game.h"
#include"SoundSystem.h"
using namespace std;
using namespace sf;
Hangman::Hangman() : attempts(0) {}

void Hangman::create() {
	srand(time(nullptr));
	int index = rand() % 100;
	category = Categories.getcategory(index);  //getting category for the hint
	word = Categories.getlist(index);  //getting word
}

string Category::getlist(int index) {
	return list[index];
}

string Hangman::DrawHangman() {
	return hangmanFigure.getmistakes(attempts);
}

string HangmanFigure::getmistakes(int attempts) {
	return mistakes_png[attempts];
}

string Category::getcategory(int index) {
	return categories1[index];
}

void Hangman::manageLives() {
	if (attempts < 7)
		attempts++;
}

int Hangman::getLives() {
	return attempts;
}

string Hangman::getcategory() const {
	return category;
}

string Hangman::getword() {
	return word;
}

//int Hangman::getScore() const {
//	return score;
//}

void Hangman::start() {
	srand(time(NULL));
	RenderWindow window(VideoMode(950, 800), "Hangman Game");

	SoundSystem music("Hangman Music.ogg",true);
	music.playBackgroundMusic();

	SoundSystem music2("Hanged.ogg", false);
	SoundSystem music3("manwon.ogg",false);

	Font font;
	if (!font.loadFromFile("Arial.ttf"))
		return;

	Text welcomeText("Welcome to Hangman!", font, 30);
	welcomeText.setPosition(50, 50);
	welcomeText.setFillColor(Color::Magenta);
	welcomeText.setStyle(Text::Bold);
	Text instructionText("Guess the word or", font, 20);
	instructionText.setPosition(50, 100);
	instructionText.setFillColor(Color::Magenta);

	Text instructionText1("Get ready to be HANGED!", font, 20);
	instructionText1.setPosition(50, 150);
	instructionText1.setFillColor(Color::Red);

	Text displayWord("", font, 40);
	displayWord.setPosition(50, 200);
	displayWord.setFillColor(Color::Black);

	Text displayWord1("", font, 30);
	displayWord1.setPosition(50, 450);
	displayWord1.setFillColor(Color::Blue);
	Text attemptsLeft("Attempts left: 6", font, 30);
	attemptsLeft.setPosition(50, 300);
	attemptsLeft.setFillColor(Color::Blue);
	Text guessedLetters("Guessed letters: ", font, 30);
	guessedLetters.setPosition(50, 350);
	guessedLetters.setFillColor(Color::Blue);

	Text message("Press Esc to pause", font, 20);
	message.setPosition(50, 650);
	message.setFillColor(Color::Blue);

	Text pausedText("Game Paused. Press 'Esc' to resume.", font, 50);
	pausedText.setPosition(50, 400);
	pausedText.setFillColor(Color::Blue);


	Text exitingText("Exiting Hangman", font, 30);
	exitingText.setPosition(50, 500);
	exitingText.setFillColor(Color::Red);

	Texture mistake_texture;
	Sprite mistake_sprite;
	if (!mistake_texture.loadFromFile("man1.png")) {
		return;
	}
	mistake_sprite.setTexture(mistake_texture);
	mistake_sprite.setPosition(400, 100);

	Hangman game;
	game.create();  //generating random word
	game.getword();
	string display(game.getword().length(), '_');    //displaying _____ in place of word
	cout << game.getword() << endl;
	sf::Text scoreText("Score: ", font, 30);
	scoreText.setString("Score: " + to_string(game.getScore())); // Updating score display
	scoreText.setPosition(50, 400);
	scoreText.setFillColor(Color::Green);

	string guessed;
	int count = 0;
	bool paused = false;
	bool gameOver = false;
	string resultMessage;

	// Game loop
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
				paused = !paused;  //pause the game when esc is pressed
			}
			else if (gameOver && event.key.code == Keyboard::Enter) {
				music.playBackgroundMusic();
				gameOver = false; 
				guessed = ""; // Clearing guessed letters
				game.create(); // generating a new word and category
				display = string(game.getword().length(), '_'); // Reseting display to masked word
				game.attempts = 0;//reseting the attempts
				attemptsLeft.setString("Attempts left: 6"); // Reseting attempts display
				if (!mistake_texture.loadFromFile("man1.png")) { // Reseting hangman image
					return;
				}
				mistake_sprite.setTexture(mistake_texture);
				mistake_sprite.setPosition(400, 100);
				resultMessage.clear();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace) {
				window.clear(sf::Color::White);
				window.draw(exitingText);
				window.draw(scoreText);
				window.display();
				sf::sleep(sf::seconds(2)); // Displaying the message for 2 seconds
				window.close();
				return; // Exiting to the main menu
			}

			if (!paused && !gameOver && event.type == Event::TextEntered) {
				char letter = static_cast<char>(event.text.unicode);
				if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
					letter = tolower(letter); //checking if entered word is letter
					

					// Checking if the letter has already been guessed
					bool letterFound = false;
					for (int i = 0; i < guessed.length(); i++) {
						int j = 0;
						if (guessed[i] == letter) {
							letterFound = true;
							break;
						}
					}

					if (!letterFound) {
						guessed += letter;  //adding the letter to the word if not found
						bool correct = false;
						count--;
						//checking if letter is in the word
						for (int i = 0; i < game.getword().length(); i++) {
							int k = 0;
							if (game.getword()[i] == letter && display[i] != letter) {
								display[i] = letter;  //updating the display with correct letter
								correct = true;
							}
						}
						//if the letter is nt correct reducing lives and hangman image
						if (!correct) {
							game.manageLives();

							if (!mistake_texture.loadFromFile(game.DrawHangman())) {
								return;
							}
							mistake_sprite.setTexture(mistake_texture);
							mistake_sprite.setPosition(400, 100);
						}
					}
					//checking if the entire word has been guessed correctly
					if (display == game.getword()) {
						music.stopBackgroundMusic();
						music3.playBackgroundMusic();
						gameOver = true;   //ending the game
						resultMessage = "Congratulations, you guessed the word!";
						game.increaseScore();
						scoreText.setString("Score: " + to_string(game.getScore())); // Updating the score display
						//displaying image for winning
						Texture mistake_texture2;
						Sprite mistake_sprite2;
						if (!mistake_texture.loadFromFile("man9.png")) {
							return;
						}
						count++;
						mistake_sprite2.setTexture(mistake_texture2);
						mistake_sprite2.setPosition(400, 100);
						window.draw(mistake_sprite2);
					}
					//checking if the lives have run out
					if (game.getLives() >= 6) {
						music.stopBackgroundMusic();
						music2.playBackgroundMusic();
						gameOver = true;  //ending the game
						resultMessage = "You lost! The word was: " + game.getword();
						Texture mistake_texture1;  //displaying image for losing
						Sprite mistake_sprite1;
						if (!mistake_texture.loadFromFile("man8.png")) {
							return;
						}
						mistake_sprite1.setTexture(mistake_texture1);
						mistake_sprite1.setPosition(400, 100);
						window.draw(mistake_sprite1);
					}
				}
			}
		}
		//updating thr words and attempts left
		displayWord.setString("Word: " + display);
		attemptsLeft.setString("Attempts left: " + to_string(6 - game.getLives()));
		displayWord1.setString("Hint: " + game.getcategory());
		guessedLetters.setString("Guessed letters: " + guessed);

		window.clear(Color::White);
		if (paused) {
			window.clear(Color::White);
			window.draw(pausedText);  // Drawing the pause message
		}
		else {
			window.draw(welcomeText);
			window.draw(instructionText);
			window.draw(instructionText1);
			window.draw(displayWord);
			window.draw(displayWord1);
			window.draw(attemptsLeft);
			window.draw(guessedLetters);
			window.draw(message);
			window.draw(mistake_sprite);
			window.draw(scoreText);
		}
		if (gameOver) {
			Text resultText(resultMessage, font, 30);
			resultText.setPosition(50, 500);
			resultText.setFillColor(Color::Red);
			window.draw(resultText);

			Text restartText("Press Enter to play again", font, 20);
			restartText.setPosition(50, 550);
			restartText.setFillColor(Color::Green);
			window.draw(restartText);
		}

		window.display();
	}
}
