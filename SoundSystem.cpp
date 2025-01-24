#include "SoundSystem.h"
using namespace std;
using namespace sf;

SoundSystem::SoundSystem(const string& str,bool vol) {
    if (!backgroundMusic.openFromFile(str)) {
       cout << "Failed to load menu.mp3!" << endl;
    }

    backgroundMusic.setLoop(vol);
    backgroundMusic.setVolume(50);
}

void SoundSystem::playBackgroundMusic() {
    backgroundMusic.play();
}

void SoundSystem::stopBackgroundMusic() {
    backgroundMusic.stop();
}

void SoundSystem::resumeBackgroundMusic() {
    if (backgroundMusic.getStatus() != Music::Playing) {
        backgroundMusic.play();
    }
}
