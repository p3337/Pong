/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#include "Puck.h"

Puck::Puck() {}

Puck::Puck(float x, float y, float r)
{
	body.setPosition(x, y);
	body.setSize(sf::Vector2f(r, r));
}

/**
\brief Moves Puck by an offset determined by velocityX and velocityY
*/
void Puck::move()
{
	body.move(sf::Vector2f(velocityX * VELOCITY, velocityY * VELOCITY));
}

sf::RectangleShape Puck::getBody()
{
	return body;
}

float Puck::getBodyX()
{
	return body.getPosition().x;
}

float Puck::getBodyY()
{
	return body.getPosition().y;
}

float Puck::getBodyR()
{
	return body.getSize().x;
}

/**
\brief Checks and reports if Puck collides with one side of the board
\return The side where the collision happened or NONE
*/
Puck::PuckCollision Puck::checkBorderCollision()
{
	PuckCollision collisionType = PuckCollision::NONE;
	
	// check LEFT and RIGHT side
	float x = getBodyX();
	float r = getBodyR();
	if (x < 0 || (x + r) > WIDTH)
	{
		this->velocityX *= -1;
		if (x < 0) collisionType = PuckCollision::LEFT;
		else collisionType = PuckCollision::RIGHT;
		
		JukeBox::getInstance().playScoreSound();
	} 
	// check TOP and BOTTOM side
	else
	{
		float y = getBodyY();
		if (y < 0 || (y + r) > HEIGHT)
		{
			this->velocityY *= -1;
			if (y < 0) collisionType = PuckCollision::TOP;
			else collisionType = PuckCollision::BOTTOM;

			JukeBox::getInstance().playBoarderSound();
		}
	}

	return collisionType;
}

/**
\brief Checks if Puck collides with one Paddle and changes direction of movement
\return True if a collision occured
*/
bool Puck::checkPaddleCollision(Paddle * paddle)
{
	bool collision = false;

	sf::FloatRect paddleBounds = paddle->getBody().getGlobalBounds();
	if (paddleBounds.intersects(body.getGlobalBounds()))
	{
		collision = true;
		this->velocityX *= -1;
		
		// calculate new y-axis-movement depending on entry point
		float paddleY = paddle->getBodyY();
		float puckY = getBodyY() - paddleY;
		float height = paddle->getBody().getSize().y;
		float percentage = puckY / height;
		if (percentage >= 0.5f)
		{
			percentage = percentage - 0.5f;
			velocityY = 1.0f * percentage;
		}
		else
		{
			percentage = 1.0f - percentage;
			velocityY = 1.0f * -percentage;
		}

		JukeBox::getInstance().playPaddleSound();
	}

	return collision;
}

/**
\brief Resets the Puck position depending on collision type
*/
void Puck::reset(PuckCollision direction)
{
	float centerX = (float) WIDTH / 2.0f;
	float centerY = (float) HEIGHT / 2.0f;

	// if no collision reset to boarder center
	if (direction == PuckCollision::NONE)
	{
		velocityX = 1.0f;
		velocityY = 0.0f;
	}
	else
	{
		if (direction == PuckCollision::LEFT)
		{
			velocityX = 1.0f;
		}
		else
		{
			velocityX = -1.0f;
		}
		velocityY = 0.5f;
		centerY = (centerY * 2.0f) / 3.0f;
	}
	body.setPosition(centerX, centerY);
}