#pragma once

class Menu {
public:
    Menu();
    int getoption();
    void navigate(int direction);
    std::string getOptionText(int index);
    void displayInstructionsScreen(sf::RenderWindow& window,sf::Font& ArialFont,sf::Font&TNRFont);
    void displayLeaderboardScreen(sf::RenderWindow& window, sf::Font& TNRFont);


private:
    std::string options[6];
    int selectedoption;
};