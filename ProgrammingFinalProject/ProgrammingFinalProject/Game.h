/// <summary>
/// Leon Nolte
/// C00263935
/// </summary>

#ifndef GAME_HPP
#define GAME_HPP

/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include <SFML/Graphics.hpp>
#include "Player.h"

const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 800;
const unsigned int FIGURE_SIZE = 32 * 4;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void setupObjects();
	void movePlayer(Direction t_direction);
	void moveUp(sf::Vector2f &t_position, sf::Sprite &t_sprite, float t_speed);
	void moveDown(sf::Vector2f& t_position, sf::Sprite& t_sprite, float t_speed);
	void moveLeft(sf::Vector2f& t_position, sf::Sprite& t_sprite, float t_speed);
	void moveRight(sf::Vector2f& t_position, sf::Sprite& t_sprite, float t_speed);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_score; // text used for message on screen
	sf::Texture m_backgroundTexture; // texture used for sfml logo
	sf::Sprite m_backgroundSprite; // sprite used for background
	bool m_exitGame; // control exiting game

	Player m_player; // player object

};

#endif // !GAME_HPP

