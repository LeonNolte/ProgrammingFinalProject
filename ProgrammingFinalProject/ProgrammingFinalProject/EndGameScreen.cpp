

#include "EndGameScreen.h"

/// <summary>
/// constructor
/// </summary>
EndGameScreen::EndGameScreen()
{
	m_finalScore.setString("Test ");
	m_finalScore.setFont(m_ArialBlackfont);
	m_finalScore.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_finalScore.setPosition(600.0f, 200.0f);
	m_finalScore.setCharacterSize(40U);
	m_finalScore.setFillColor(sf::Color::Black);

	m_killedStabbers.setFont(m_ArialBlackfont);
	m_killedStabbers.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_killedStabbers.setPosition(WINDOW_WIDTH / 2.0f, 300.0f);
	m_killedStabbers.setCharacterSize(50U);
	m_killedStabbers.setFillColor(sf::Color::Black);

	m_killedThrowers.setFont(m_ArialBlackfont);
	m_killedThrowers.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_killedThrowers.setPosition(WINDOW_WIDTH / 2.0f, 400.0f);
	m_killedThrowers.setCharacterSize(50U);
	m_killedThrowers.setFillColor(sf::Color::Black);

	m_timeSurvived.setFont(m_ArialBlackfont);
	m_timeSurvived.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_timeSurvived.setPosition(WINDOW_WIDTH / 2.0f, 500.0f);
	m_timeSurvived.setCharacterSize(50U);
	m_timeSurvived.setFillColor(sf::Color::Black);
}

/// <summary>
/// displays score to screen
/// </summary>
/// <param name="t_score"> score as int </param>
void EndGameScreen::displayScore(int t_score)
{
	m_finalScore.setString("Final Score: " + std::to_string(t_score));
}

/// <summary>
/// displays stats to screen
/// </summary>
/// <param name="t_killedStabbers"> number of stabbers killed </param>
/// <param name="t_killedThrowers"> number of throwers killed </param>
void EndGameScreen::displayStats(short t_killedStabbers, short t_killedThrowers)
{
	m_killedStabbers.setString("Stabbers Killed: " + std::to_string(t_killedStabbers));
	m_killedThrowers.setString("Throwers Killed: " + std::to_string(t_killedThrowers));
}

/// <summary>
/// displays time survived 
/// </summary>
/// <param name="t_timeSurvived"> survival time </param>
void EndGameScreen::displaySurvivalTime(int t_timeSurvived)
{
	m_timeSurvived.setString("Time Survived: " + std::to_string(t_timeSurvived));
}
