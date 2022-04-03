// End of game screen
// Displays final score and stats about killed enemies
// Player may press R to re-play game

#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <string>

class EndGameScreen
{
public:

	EndGameScreen();

	sf::Text getScore() { return m_finalScore; };
	sf::Text getKilledThrowers() { return m_killedThrowers; };
	sf::Text getKilledStabbers() { return m_killedStabbers; };
	sf::Text getSurvivalTime() { return m_timeSurvived; };

	void displayScore(int t_score);
	void displayStats(short t_killedStabbers, short t_killedThrowers);
	void displaySurvivalTime(int t_timeSurvived);

private:

	sf::Text m_finalScore; // final player score
	sf::Text m_killedStabbers; // number of stabbers killed
	sf::Text m_killedThrowers; // number of throwers killed 
	sf::Text m_timeSurvived; // time survived
	sf::Font m_ArialBlackfont; // font used by message

};

