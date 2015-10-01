/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#undef UNICODE
#define UNICODE

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Board.h"
#include "Variables.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), TITLE, sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	// Load the text font
	sf::Font font;
	if (!font.loadFromFile(FONT_PATH)) __nop();

	// Initialize the start / end message
	sf::Text msgStart;
	msgStart.setFont(font);
	msgStart.setCharacterSize(40);
	msgStart.setPosition((float) WIDTH / 6.0f, (float) HEIGHT / 4.0f);
	msgStart.setColor(sf::Color::Red);
	msgStart.setString(MSG_START);

	// create both players
	Player playerLeft = Player(sf::Keyboard::Key::A, sf::Keyboard::Key::Y, sf::Color::Blue, Player::Side::LEFT);
	Player playerRight = Player(sf::Keyboard::Key::K, sf::Keyboard::Key::M, sf::Color::Red, Player::Side::RIGHT);
	std::vector<Player*> players = { &playerLeft, &playerRight };

	// create board
	Board board = Board(&players);

	// start main loop
	bool isPlaying = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					// (re)start the game
					isPlaying = true;
				}
			}
		}

		window.clear(sf::Color(33, 33, 33));

		if (isPlaying)
		{
			// check if game has ended and reset it
			if (!board.update(&window))
			{
				isPlaying = false;

				char buff[100];
				snprintf(buff, sizeof(buff), MSG_END.toAnsiString().c_str(), playerLeft.getScore() >= WIN_POINTS ? 0 : 1);
				std::string buffAsStdStr = buff;
				msgStart.setString(buffAsStdStr);
				board.reset();
			}
		}
		else
		{
			window.draw(msgStart);
		}
		
		window.display();
	}

	return 0;
}