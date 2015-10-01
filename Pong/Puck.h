#pragma once

#ifndef PUCK_H
#define PUCK_H

#include <SFML/Graphics.hpp>
#include "Variables.h"
#include "Paddle.h"
#include "JukeBox.h"

class Puck {
	public:
		Puck();
		Puck(float x, float y, float r);
		sf::RectangleShape getBody();
		void move();
		enum PuckCollision { NONE, TOP, RIGHT, BOTTOM, LEFT };
		PuckCollision checkBorderCollision();
		bool checkPaddleCollision(Paddle * paddle);
		float getBodyX();
		float getBodyY();
		float getBodyR();
		void reset(PuckCollision direction);

	private:
		float velocityX = 1.0f;
		float velocityY = 0.0f;
		sf::RectangleShape body;
};

#endif // !PUCK_H
