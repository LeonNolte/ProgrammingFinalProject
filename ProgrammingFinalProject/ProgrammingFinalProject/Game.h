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
#include "Stabber.h"
#include "MyVector2.h" // taken from Maths Lab Project "My Vector2f"
#include <iostream>

const unsigned int WINDOW_WIDTH = 1200; // window width
const unsigned int WINDOW_HEIGHT = 800; // window height
const unsigned int FIGURE_SIZE = 32 * 4; // size of characters
const unsigned short NUMBER_STABBERS = 6; // number of Stabber enemies

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

	// game loop functions
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	// setup
	void setupFontAndText();
	void setupSprite();
	void setupObjects();

	// movement functions
	void movePlayer(Direction t_direction);
	void moveUp(sf::Vector2f &t_position, sf::Vector2f t_velocity);
	void moveDown(sf::Vector2f& t_position, sf::Vector2f t_velocity);
	void moveLeft(sf::Vector2f& t_position, sf::Vector2f t_velocity);
	void moveRight(sf::Vector2f& t_position, sf::Vector2f t_velocity);
	void stabberFollowPlayer();


	// data members
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_score; // text used for message on screen
	sf::Texture m_backgroundTexture; // texture used for sfml logo
	sf::Sprite m_backgroundSprite; // sprite used for background
	bool m_exitGame; // control exiting game

	// objects
	Player m_player; // Player object
	Stabber m_stabberKobold[NUMBER_STABBERS]; // array of Stabber Kobolds

};

#endif // !GAME_HPP

