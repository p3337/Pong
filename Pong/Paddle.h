#pragma once

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "Variables.h"

class Paddle {
	
	public:
		Paddle();
		Paddle(float x, float y, float width, float height, sf::Color color);
		void moveUp();
		void moveDown();
		sf::RectangleShape getBody();
		float getBodyX();
		float getBodyY();
		void reset();
	
	private:
		sf::RectangleShape body;
		float x;
		float y;

};

#endif // !PADDLE_H
