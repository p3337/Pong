/**
* @author Peter Hansen
* @copyright p3337.de All rights reserved.
*/
#include "JukeBox.h"

JukeBox::JukeBox() {
	loadSounds();
}

// Load the sounds used in the game
void JukeBox::loadSounds() {
	if (!boarderSoundBuffer.loadFromFile("resources/unclick.wav")) __nop();
	boarderSound.setBuffer(boarderSoundBuffer);

	if (!paddleSoundBuffer.loadFromFile("resources/menu1.wav")) __nop();
	paddleSound.setBuffer(paddleSoundBuffer);

	if (!scoreSoundBuffer.loadFromFile("resources/launch_deny2.wav")) __nop();
	scoreSound.setBuffer(scoreSoundBuffer);
}

void JukeBox::playBoarderSound() {
	boarderSound.play();
}

void JukeBox::playPaddleSound() {
	paddleSound.play();
}

void JukeBox::playScoreSound() {
	scoreSound.play();
}