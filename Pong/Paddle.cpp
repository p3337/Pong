/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#include "Paddle.h"

Paddle::Paddle(){}

Paddle::Paddle(float x, float y, float width, float height, sf::Color color) : x(x), y(y)
{
	body.setPosition(x, y);
	body.setSize(sf::Vector2f(width, height));
	body.setOutlineThickness(2.0f);
	body.setFillColor(color);
}

/**
\brief Moves the paddle up until to an edge of the board 
*/
void Paddle::moveUp()
{
	float y = body.getPosition().y;
	float outlineThickness = body.getOutlineThickness();
	if (y > outlineThickness)
	{
		body.move(sf::Vector2f(0.0f, -1.0f * VELOCITY));
	}
	else
	{
		body.setPosition(body.getPosition().x, outlineThickness);
	}
}

/**
\brief Moves the paddle down until to an edge of the board
*/
void Paddle::moveDown()
{
	float y = body.getPosition().y;
	float outlineThickness = body.getOutlineThickness();
	float maxHeight = (float) HEIGHT - body.getSize().y - outlineThickness;
	if (y < maxHeight)
	{
		body.move(sf::Vector2f(0.0f, 1.0f * VELOCITY));
	}
	else
	{
		body.setPosition(body.getPosition().x, maxHeight);
	}
}

sf::RectangleShape Paddle::getBody()
{
	return body;
}

float Paddle::getBodyX()
{
	return body.getPosition().x;
}

float Paddle::getBodyY()
{
	return body.getPosition().y;
}


/**
\brief Resets the Paddle to the vertical center
*/
void Paddle::reset()
{
	body.setPosition(x, y);
}