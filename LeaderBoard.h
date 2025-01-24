#pragma once
#include"PlayerProfile.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class LeaderBoard
{
	Player* player;
public:
	void filedata(sf::RenderWindow& window,sf::Font& TNRFont);

};