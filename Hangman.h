#ifndef Hangman_H
#define Hangman_H
#include <string>
using namespace std;
#include "Game.h"
class Category {
private:
    const string list[100] = { "apple", "banana", "orange", "grape", "strawberry", "cat", "dog", "elephant", "lion", "tiger", "house", "car", "tree", "flower", "sun",
                      "happy", "sad", "angry", "laugh", "red", "blue", "green", "yellow", "purple", "two", "three", "four", "five", "ocean", "river", "mountain", "desert", "forest",
                      "computer", "phone", "keyboard", "mouse", "screen", "book", "pen", "pencil", "paper", "notebook", "music", "dance", "sing", "paint", "draw",
                      "pizza", "burger", "pasta", "cake", "icecream", "school", "teacher", "student", "class", "homework", "friend", "family", "winter", "summer", "spring", "fall",
                      "season", "watch", "clock", "time", "hour", "minute", "run", "jump", "swim", "walk", "crawl", "sleep", "eat", "drink", "play", "work",
                      "star", "moon", "planet", "space", "rocket", "fish", "bird", "turtle", "snake", "elephant", "hat", "shoe", "shirt", "pants", "socks", "happy", "sad", "angry",
                      "laugh", "cry"};
    const string categories1[100] = {
      "Fruits", "Fruits", "Fruits", "Fruits", "Fruits", // apple, banana, orange, grape, strawberry
      "Animals", "Animals", "Animals", "Animals", "Animals", // cat, dog, elephant, lion, tiger
      "Household/Places", "Household/Places", "Household/Places", "Household/Places", "Nature", // house, car, tree, flower, sun
      "Emotions", "Emotions", "Emotions", "Emotions", "Colors", // happy, sad, angry, laugh, red
      "Colors", "Colors", "Colors", "Colors", "Numbers", // blue, green, yellow, purple, two
      "Numbers", "Numbers", "Numbers", "Nature", "Nature", // three, four, five, ocean, river
      "Nature", "Nature", "Technology", "Technology", "Technology", // mountain, desert, forest, computer, phone
      "Technology", "Technology", "Stationery", "Stationery", "Stationery", // keyboard, mouse, screen, book, pen
      "Stationery", "Stationery", "Art", "Art", "Art", // pencil, paper, music, dance, sing
      "Art", "Art", "Food", "Food", "Food", // paint, draw, pizza, burger, pasta
      "Food", "Food", "School", "School", "School", // cake, icecream, school, teacher, student
      "School", "Family", "Family", "Seasons", "Seasons", // class, homework, friend, family, winter
      "Seasons", "Seasons", "Seasons", "Time", "Time", // summer, spring, fall, season, watch
      "Time", "Time", "Time", "Actions", "Actions", // clock, time, hour, minute, run
      "Actions", "Actions", "Actions", "Actions", "Actions", // jump, swim, walk, crawl, sleep
      "Actions", "Actions", "Actions", "Actions", "Space", // eat, drink, play, work, star
      "Space", "Space", "Space", "Space", "Animals", // moon, planet, space, rocket, fish
      "Animals", "Animals", "Animals", "Animals", "Clothing", // bird, turtle, snake, elephant, hat
      "Clothing", "Clothing", "Clothing", "Clothing", "Emotions", // shoe, shirt, pants, socks, happy
      "Emotions", "Emotions", "Emotions", "Emotions","Emotions" // sad, angry, laugh, cry
    };
public:
   
    string getcategory(int index);
    string getlist(int index);
    
};
class HangmanFigure {
private:
    const char mistakes_png[8][20] = { "man2.png","man2.png","man3.png","man4.png","man5.png","man6.png","man7.png" ,"man8.png" };
public:
    string getmistakes(int attempt);
};

class Hangman : public Game {
private:
    int attempts;
    string word;
    Category Categories;
    string category;
    HangmanFigure hangmanFigure;
public:
    void create();
    string getword();
    string getcategory() const;
    string DrawHangman();
    void manageLives();
    int getLives();
    Hangman();
    void start() override;
};


#endif