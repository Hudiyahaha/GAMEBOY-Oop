#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include<string>
class SoundSystem {
public:
    SoundSystem(const std::string& str,bool vol);
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void resumeBackgroundMusic();

private:
    sf::Music backgroundMusic;
};
