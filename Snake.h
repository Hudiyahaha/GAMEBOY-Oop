#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
using namespace sf;

class Snake :public Game {
public:
    enum Direction { None, Up, Down, Left, Right };
    void start() override;
    Snake();
    Snake(int blockSize);
    ~Snake();

    void setDirection(Direction dir);
    Direction getDirection() const;
    int getScore() const;
    bool hasLost() const;

    void lose();
    void toggleLost();

    void extend();
    void reset();
    bool checkEasterEggCollision(const Vector2i& eggPosition);

    void move();
    void tick();
    void render(RenderWindow& window);

    bool checkFoodCollision(const Vector2i& foodPosition);

private:
    void checkCollision();

    static const int MAX_SNAKE_LENGTH = 100;
    Vector2i m_snakeBody[MAX_SNAKE_LENGTH];
    int m_size;
    int snakeLength;
    Direction m_dir;
    bool lostlife;
    Texture bodyTexture;
    Sprite bodySprite;
    int m_lives;
    Sound gameOverSound; // Add gameOverSound member variable
};

class Food {
public:
    Food(int blockSize);
    ~Food();

    void respawn();
    void render(RenderWindow& window);
   Texture foodTexture;
   Sprite foodSprite;
   Vector2i getPosition() const;

private:
   Vector2i m_position;
    int m_size;
 //  RectangleShape m_foodRect;
};

class EasterEgg {
public:
    EasterEgg(int blockSize);
    ~EasterEgg();

    void respawn();
    void render(RenderWindow& window);
    Vector2i getPosition() const;
private:
    int m_size;
    Vector2i m_position;
    Texture eggTexture;
    Sprite eggSprite;
};



#endif // SNAKE_H
