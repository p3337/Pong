/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#include "Board.h"

Board::Board(std::vector<Player*> * players) : players(players), puck(), scoreText()
{
	float centerX = (float) WIDTH / 2.0f;
	float centerY = (float) HEIGHT / 2.0f;

	// create score text
	if (!font.loadFromFile(FONT_PATH)) __nop();
	scoreText.setFont(font);
	scoreText.setString("0   0");
	scoreText.setCharacterSize(55);
	scoreText.setStyle(sf::Text::Bold);
	centerText(&scoreText);

	// create dashed line as a divider in the middle
	float gapSize = (float)HEIGHT / (float)numberOfLines;
	for (int i = 0; i < numberOfLines; i++)
	{
		sf::Vertex vertex(sf::Vector2f(centerX, gapSize * (float)i));
		if (i % 2 == 0) vertex.color = sf::Color::Black;
		line[i] = vertex;
	}

	// create puck
	puck = Puck(centerX, centerY, 16.0f);
}

/**
\brief Centers the given sf::Text
*/
void Board::centerText(sf::Text * txt)
{
	float centerX = (float) WIDTH / 2.0f;
	sf::FloatRect textRect = txt->getLocalBounds();
	txt->setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	txt->setPosition(sf::Vector2f(centerX, 40));
}

/**
\brief Updates the current game status and draws the results on the window
\return False if game has ended true otherwise
*/
bool Board::update(sf::RenderWindow * window)
{
	// handle players
	for each (Player * player in *players)
	{
		player->HandleKeyInput();
		window->draw(player->getPaddle().getBody());
	}

	window->draw(line, numberOfLines, sf::Lines);

	// handle puck
	puck.move();
	switch (puck.checkBorderCollision())
	{
		case Puck::PuckCollision::LEFT:
		case Puck::PuckCollision::RIGHT:
		{
			// increase score of successful player
			players->at(puck.checkBorderCollision() == Puck::PuckCollision::LEFT ? 1 : 0)->increaseScore();

			// update current scores
			int p0_score = players->at(0)->getScore();
			int p1_score = players->at(1)->getScore();
			scoreText.setString(std::to_string(p0_score) + "   " + std::to_string(p1_score));
			centerText(&scoreText);

			// reset puck for next round
			puck.reset(puck.checkBorderCollision());

			// game over?
			if (p0_score >= WIN_POINTS || p1_score >= WIN_POINTS)
			{
				return false;
			}
		}
		break;
		
		case Puck::PuckCollision::NONE:
		{
			for each (Player * player in *players)
			{
				if (puck.checkPaddleCollision(&player->getPaddle())) break;
			}
		}
		break;
	}
	window->draw(scoreText);
	window->draw(puck.getBody());

	return true;
}


/**
\brief Resets the Board and all its components
*/
void Board::reset()
{
	for each (Player * player in *players)
	{
		player->reset();
	}
	puck.reset(Puck::PuckCollision::NONE);
	scoreText.setString("0   0");
	centerText(&scoreText);
}