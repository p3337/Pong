#pragma once

#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Puck.h"

class Board {
	public:
		Board(std::vector<Player*> * players);
		std::vector<Player*> * players;
		Puck puck;
		bool update(sf::RenderWindow * window);
		void reset();

	private:
		void centerText(sf::Text * txt);
		sf::Font font;
		sf::Text scoreText;
		static const int numberOfLines = 100;
		sf::Vertex line[numberOfLines];

};

#endif // !BOARD_H
