#ifndef Wordle_H
#define Wordle_H
#include<string>
 #include "Game.h"
using namespace std;

class WordDictionary {
private:
    const string list[100] = {
    "apple", "grape", "berry", "lemon", "peach","mango", "melon", "plums", "guava", "cherry","toast", "bread", "pizza", "pasta", "tacos",
    "chair", "table", "couch", "stool", "shelf","cloud", "storm", "sunny", "windy", "snowy","brush", "paint", "craft", "write", "draws",
    "brick", "steel", "glass", "stone", "paper","horse", "zebra", "snake", "mouse", "tiger","apple", "peach", "melon", "guava", "plums",
    "swims", "jumps", "dance", "plays", "sings","sharp", "round", "blunt", "quick", "smart","earth", "space", "alien", "orbit", "comet",
    "start", "begin", "smile", "happy", "laugh","shine", "glows", "twist", "picks", "throw","trust", "brave", "clean", "great", "proud",
    "plane", "truck", "train", "coach", "scoot","build", "house", "shack", "lodge", "tower","robot", "tools", "wires", "chips", "board"
    };
public:
    string getlist(int index);
};
class Letter {
private:

};
class WordleGame:public Game  {
private:
    string word;
    WordDictionary Dictionary;
    int score=0; 
public:
    string randword();
    void start() override;
    
};


#endif
