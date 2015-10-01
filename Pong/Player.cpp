/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#include "Player.h"

Player::Player(sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown, sf::Color color, Side side): keyUp(keyUp), keyDown(keyDown), paddle()
{
	float paddleX = 10.0f;
	float paddleY = (float) HEIGHT / 2.0f;
	float paddleWidth = 20.0f;
	float paddleHeight = 150.0f;

	if (side == Side::RIGHT)
	{
		paddleX = (float) WIDTH - paddleX - paddleWidth;
	}
	paddleY -= paddleHeight / 2.0f;

	paddle = Paddle(paddleX, paddleY, paddleWidth, paddleHeight, color);
}

/**
\brief Checks if player pressed a key to move paddle
*/
void Player::HandleKeyInput()
{
	if (sf::Keyboard::isKeyPressed(keyUp))
	{
		paddle.moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(keyDown))
	{
		paddle.moveDown();
	}
}

Paddle Player::getPaddle()
{
	return paddle;
}

void Player::increaseScore()
{
	score++;
}

int Player::getScore()
{
	return score;
}

void Player::reset()
{
	score = 0;
	paddle.reset();
}