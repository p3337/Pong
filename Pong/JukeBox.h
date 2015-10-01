#pragma once

#ifndef JUKE_BOX_H
#define JUKE_BOX_H

#include <SFML/Audio.hpp>

class JukeBox {
	public:
		static JukeBox& getInstance()
		{
			static JukeBox instance;
			return instance;
		}

		void playBoarderSound();
		void playPaddleSound();
		void playScoreSound();

	private:
		JukeBox();

		JukeBox(JukeBox const&) = delete;
		void operator=(JukeBox const&) = delete;

		void loadSounds();

		sf::SoundBuffer boarderSoundBuffer;
		sf::Sound boarderSound;

		sf::SoundBuffer paddleSoundBuffer;
		sf::Sound paddleSound;

		sf::SoundBuffer scoreSoundBuffer;
		sf::Sound scoreSound;
};

#endif // !JUKE_BOX_H

