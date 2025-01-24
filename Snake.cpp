// Snake Game using C++ and SFML
#include "Snake.h"
#include <iostream>
#include <cstdlib>
#include "Game.h"
#include"SoundSystem.h"
using namespace sf;
using namespace std;

// Snake class 
Snake::Snake() : m_lives(3) { // Initialize lives

}

EasterEgg::EasterEgg(int blockSize) : m_size(blockSize) {
    if (!eggTexture.loadFromFile("easter.png")) {
        cerr << "Error loading easter_egg.png" << endl;
    }
    bool f = false;

    m_position.x = (rand() % (800 / m_size));
    m_position.y = (rand() % (600 / m_size));
    eggSprite.setPosition(
        (float)(m_position.x * m_size),
        (float)(m_position.y * m_size)
    );
    eggSprite.setTexture(eggTexture);
    eggSprite.setScale(
        (float)(m_size) / eggTexture.getSize().x,
        (float)(m_size) / eggTexture.getSize().y
    );
    respawn();
}

EasterEgg::~EasterEgg() {}

void EasterEgg::respawn() {
    m_position.x = rand() % (800 / m_size);
    m_position.y = rand() % (600 / m_size);
    eggSprite.setPosition((float)(m_position.x * m_size), (float)(m_position.y * m_size));
}

void EasterEgg::render(RenderWindow& window) {
    window.draw(eggSprite);
}

Vector2i EasterEgg::getPosition() const {
    return m_position;
}

Snake::Snake(int blockSize) : m_size(blockSize), snakeLength(3), m_dir(Direction::None), lostlife(false), m_lives(3) { // Initialize lives
    if (!bodyTexture.loadFromFile("Snake Body.png")) {
        cerr << "Error loading Snake Body.png" << endl;
    }
    bodySprite.setTexture(bodyTexture);
    bodySprite.setScale((float)(m_size) / bodyTexture.getSize().x, (float)(m_size) / bodyTexture.getSize().y);
    reset();
}

Snake::~Snake() {}

void Snake::setDirection(Direction dir) {
    m_dir = dir;
}

Snake::Direction Snake::getDirection() const {
    return m_dir;
}

int Snake::getScore() const {
    return Game::getScore();
}

bool Snake::hasLost() const {
    return lostlife;
}

void Snake::lose() {
    lostlife = true;
    m_lives--; // Decrease lives
    gameOverSound.play();
}
void Snake::toggleLost() {
    lostlife = !lostlife;
}

void Snake::extend() {
    int len=0;
    if (snakeLength < MAX_SNAKE_LENGTH) {
        m_snakeBody[snakeLength] = m_snakeBody[snakeLength - 1];
        ++snakeLength;
        len++;
    }
}

bool Snake::checkEasterEggCollision(const Vector2i& eggPosition) {
    if (m_snakeBody[0].x == eggPosition.x && m_snakeBody[0].y == eggPosition.y) {
        extend();
        // Egg Bonuss
        int egg = 0;
        while (egg < 5)
            egg++;

        Game::increaseScoreBy30();
        return true;
    }
}

void Snake::reset() {
    snakeLength = 3;
    m_snakeBody[0] = Vector2i(5, 7);
    m_snakeBody[1] = Vector2i(5, 6);
    m_snakeBody[2] = Vector2i(5, 5);
    setDirection(Direction::None);
    lostlife = false;
}

void Snake::move() {
    // Check for collision with the window boundaries before moving
    Vector2i nextPosition = m_snakeBody[0];
    if (m_dir == Direction::Left) {
        --nextPosition.x;
    }
    else if (m_dir == Direction::Right) {
        ++nextPosition.x;
    }
    else if (m_dir == Direction::Up) {
        --nextPosition.y;
    }
    else if (m_dir == Direction::Down) {
        ++nextPosition.y;
    }

    if (nextPosition.x < 0 || nextPosition.x >= 800 / m_size || nextPosition.y < 0 || nextPosition.y >= 600 / m_size) {
        lose();
        return;
    }

    for (int i = snakeLength - 1; i > 0; --i) {
        m_snakeBody[i] = m_snakeBody[i - 1];
    }

    m_snakeBody[0] = nextPosition;

    checkCollision();
}

void Snake::tick() {
    if (snakeLength == 0 || m_dir == Direction::None) return;
    move();
}

void Snake::render(RenderWindow& window) {
    if (snakeLength == 0) return;

    for (int i = 0; i < snakeLength; ++i) {
        bodySprite.setPosition((float)(m_snakeBody[i].x * m_size), (float)(m_snakeBody[i].y * m_size));
        window.draw(bodySprite);
    }

    // Render lives as smaller red squares at the top right corner
   /* RectangleShape lifeRect(Vector2f(15, 15));
    lifeRect.setFillColor(Color::Red);*/

    Texture lives;
    if (!lives.loadFromFile("apple2.png")) {
        cerr << "Error loading apple.png" << endl;
    }
    Sprite lives_sprite;
    lives_sprite.setTexture(lives);

    lives_sprite.setScale(
        (float)(m_size) / lives.getSize().x,
        (float)(m_size) / lives.getSize().y
    );

    int ff = 0;
    for (int i = 0; i < m_lives; ++i) {
        lives_sprite.setPosition(715 + i * 28, 10);
        window.draw(lives_sprite);
    }
}

void Snake::checkCollision() {
    if (snakeLength < 5) return;

    Vector2i& head = m_snakeBody[0];
    for (int i = 1; i < snakeLength; ++i) {
        if (m_snakeBody[i] == head) {
            lose();
            break;
        }
    }
}

bool Snake::checkFoodCollision(const Vector2i& foodPosition) {
    if (m_snakeBody[0] == foodPosition) {
        extend();
        Game::increaseScore(); // Call the increaseScore method from the Game class
        return true;
    }
    return false;
}

// Food class implementation
Food::Food(int blockSize) : m_size(blockSize) {
   if (!foodTexture.loadFromFile("apple2.png")) {
		cerr << "Error loading apple.png" << endl;
	}
	foodSprite.setTexture(foodTexture);

	foodSprite.setScale(
        (float)(m_size) / foodTexture.getSize().x,
        (float)(m_size) / foodTexture.getSize().y
	);
    respawn();
}

Food::~Food() {}

void Food::respawn() {
	m_position.x = rand() % (800 / m_size);
	m_position.y = rand() % (600 / m_size);
    foodSprite.setPosition((float)(m_position.x * m_size), (float)(m_position.y * m_size));
}

void Food::render(RenderWindow& window) {
	window.draw(foodSprite);
}

Vector2i Food::getPosition() const {
    return m_position;
}

void Snake::start() {
    RenderWindow window(VideoMode(800, 600), "Snake Game");

    // Load background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Snake Back.jpg")) {
        cerr << "Error loading Snake Back.jpg" << endl;
        return;
    }
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Load font
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error loading arial.ttf" << endl;
        return;
    }

    // Create score text
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    // Create score text for exiting
    Text scoreText2("Score: ", font, 30);
    scoreText2.setPosition(50, 400);
    scoreText2.setFillColor(Color::Green);

    // Create game over text
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Game Over!\nPress Enter to Restart");
    gameOverText.setPosition(200, 250);

    // Create exiting text
    Text exitingText("Exiting Snake", font, 30);
    exitingText.setPosition(200, 300);
    exitingText.setFillColor(Color::Red);

    Text pausedText("Game Paused. Press 'Esc' to resume.", font, 30);
    pausedText.setPosition(30, 300);
    pausedText.setFillColor(Color::Blue);

    SoundSystem eastersound("easter.wav",false);
    SoundSystem foodSound("food.wav", false);
    SoundSystem backgroundMusic("Mr Bean.mp3",true);
    
    backgroundMusic.playBackgroundMusic();

    Snake snake(20);

    SoundBuffer gameOverBuffer;
    if (!gameOverBuffer.loadFromFile("gameover.wav")) {
        cerr << "Error loading gameover.wav" <<endl;
        return;
    }

    Sound gameOverSound;
    gameOverSound.setBuffer(gameOverBuffer);
    snake.gameOverSound = gameOverSound; // Initialize gameOverSound

    Food food(20);
    
    Clock clock;
    float deltaTime = 0.0f;
    bool gameOverSoundPlayed = false; // Flag to track if game over sound has been played
    bool paused = false;
    bool k = false;
    EasterEgg easterEgg(20);
    Clock easterEggClock;
    float easterEggSpawnDelay = 3.0f; // Delay in seconds

    while (window.isOpen()) {
        k = false;
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                paused = !paused;  // Toggle pause state
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    snake.setDirection(Snake::Direction::Up);
                }
                else if (event.key.code == Keyboard::Down) {
                    snake.setDirection(Snake::Direction::Down);
                }
                else if (event.key.code == Keyboard::Left) {
                    snake.setDirection(Snake::Direction::Left);
                }
                else if (event.key.code == Keyboard::Right) {
                    snake.setDirection(Snake::Direction::Right);
                }
                else if (event.key.code == Keyboard::Enter && snake.hasLost() && snake.m_lives > 0) {
                    snake.reset();
                    food.respawn();
                    gameOverSoundPlayed = false; // Reset the flag when the game restarts
                }
                else if (event.key.code == Keyboard::BackSpace || snake.m_lives == 0) {
                    scoreText2.setString("Score: " + to_string(snake.getScore())); // Update scoreText2 with the current score
                    window.clear(Color::White);
                    window.draw(exitingText);
                    window.draw(scoreText2);
                    window.display();
                    sleep(seconds(2)); // Display the message for 2 seconds
                    backgroundMusic.stopBackgroundMusic();
                    k = true;
                    window.close();
                    return; // Exit to the main menu
                }
            }
        }

        //if (!paused) {
        //    deltaTime += clock.restart().asSeconds();
        //    if (deltaTime >= 0.1f) {
        //        if (!snake.hasLost()) {
        //            snake.tick();
        //            if (snake.checkFoodCollision(food.getPosition())) {
        //                food.respawn();
        //                foodSound.playBackgroundMusic(); // Play food collection sound
        //            }
        //        }
        //        deltaTime = 0.0f;
        //    }
        //    // Update score text
        //    scoreText.setString("Score: " + std::to_string(snake.getScore()));
        //    window.clear();
        //    window.draw(backgroundSprite); // Draw the background
        //    snake.render(window);
        //    food.render(window);
        //    window.draw(scoreText); // Draw the score
        //    if (snake.hasLost()) {
        //        window.draw(gameOverText); // Draw the game over message
        //        window.display();
        //        while (window.isOpen() && snake.hasLost() && snake.m_lives > 0) {
        //            while (window.pollEvent(event)) {
        //                if (event.type == Event::Closed) {
        //                    window.close();
        //                }
        //                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
        //                    snake.reset();
        //                    food.respawn();
        //                    gameOverSoundPlayed = false; // Reset the flag when the game restarts
        //                }
        //            }
        //        }
        //    }
        //    else {
        //        window.display();
        //    }
        //}
        //else {
        //    window.clear(Color::White);
        //    window.draw(pausedText);  // Draw pause message
        //    window.display();
        //}
       
        if (snake.checkEasterEggCollision(easterEgg.getPosition())) {
            k = true;
            easterEgg.respawn();
            eastersound.playBackgroundMusic(); // Play sound when egg is eaten
        }

        if (!paused) {
            deltaTime += clock.restart().asSeconds();
            if (deltaTime >= 0.1f) {
                if (!snake.hasLost()) {
                    snake.tick();
                    if (snake.checkFoodCollision(food.getPosition())) {
                        food.respawn();
                        foodSound.playBackgroundMusic(); // Play food collection sound
                    }
                    if (k) {
                        easterEggClock.restart(); // Reset the clock when the easter egg is eaten
                    }
                }
                deltaTime = 0.0f;
            }
            // Spawn the easter egg with a delay
            if (easterEggClock.getElapsedTime().asSeconds() >= easterEggSpawnDelay) {
                easterEgg.respawn();
                easterEggClock.restart();
            }

            // Update score text
            scoreText.setString("Score: " + to_string(snake.getScore()));

            window.clear();
            window.draw(backgroundSprite); // Draw the background
            snake.render(window);
            food.render(window);
            easterEgg.render(window); // Render the easter egg
            window.draw(scoreText); // Draw the score

            if (snake.hasLost()) {
                window.draw(gameOverText); // Draw the game over message

                window.display();
                while (window.isOpen() && snake.hasLost() && snake.m_lives > 0) {
                    while (window.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window.close();
                        }
                        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                            snake.reset();
                            food.respawn();
                            easterEgg.respawn();
                            gameOverSoundPlayed = false; // Reset the flag when the game restarts
                        }
                    }
                }
            }
            else {
                window.display();
            }
        }
        else {
            window.clear(Color::White);
            window.draw(pausedText);  // Draw pause message
            window.display();
        }
    }
}
    

// Main function
//int main() {
//  
//
//    return 0;
//}

