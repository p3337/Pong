#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Variables.h"

class Player {
	public:
		enum Side { LEFT, RIGHT };
		Player(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown, sf::Color color, Side side);
		void HandleKeyInput();
		Paddle getPaddle();
		void increaseScore();
		int getScore();
		void reset();

	private:
		sf::Keyboard::Key keyUp;
		sf::Keyboard::Key keyDown;
		int score = 0;
		Paddle paddle;
};

#endif // !PLAYER_H
