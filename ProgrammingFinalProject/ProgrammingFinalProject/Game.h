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

#include <SFML/Graphics.hpp> // for graphics
#include "Player.h"
#include "Stabber.h"
#include "Thrower.h"
#include "MyVector2.h" // taken from Maths Lab Project "My Vector2f"
#include <iostream> // for testing and error message display
#include <string> // for string functions (score display)
#include "EndGameScreen.h"

enum class EnemyType {
	stabber,
	thrower
};


const unsigned int FIGURE_SIZE = 32 * 3; // size of characters
const unsigned short MAX_STABBERS = 22; // max number of Stabber enemies
const unsigned short MAX_THROWERS = 20; // max number of throwers
const unsigned short SCORE_PER_STABBER = 25;
const unsigned short SCORE_PER_THROWER = 100;

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
	void processMouseClikcs(sf::Event t_event);
	void processMouseReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	// setup
	void setupFontAndText();
	void setupSprite();
	void setupObjects();

	// character movement functions
	void movePlayer(Direction t_direction);
	void moveUp(sf::Vector2f &t_position, sf::Vector2f t_velocity);
	void moveDown(sf::Vector2f& t_position, sf::Vector2f t_velocity);
	void moveLeft(sf::Vector2f& t_position, sf::Vector2f t_velocity);
	void moveRight(sf::Vector2f& t_position, sf::Vector2f t_velocity);

	// update functions
	void updatePlayer();
	void updateEnemies();
	void updateStabbers();
	void updateThrowers();

	// projectile update functions
	void updateArrow();
	void updateJavelin(Javelin& t_javelin);

	// enemy movement
	void throwerKeepDistance(sf::Vector2f &t_velocity, sf::Vector2f &t_location, int index);
	void throwerRunAway(sf::Vector2f& t_velocity, sf::Vector2f& t_location);
	void throwerEnter(short t_index);
	void stabberEnter(short t_index);
	void enemyZigZag(sf::Vector2f& t_position, int t_arrayIndex);
	float getDistanceToPlayer(sf::Vector2f& t_position, int t_arrayIndex, EnemyType t_enemy);

	// misc functions
	bool checkDespawnThrower(sf::Vector2f t_location);
	void adjustHitbox(sf::FloatRect &t_hitbox, float t_width, float t_height);
	void endGame();
	void resetGame();

	// animation functions
	void animateCharacter(sf::Sprite &t_sprite, Direction t_movementDirection);

	// collision detection functions
	bool stabberhitDetection(sf::Sprite& t_stabberSprite);
	bool arrowHitDetection(sf::Vector2f t_position);
	bool javelinHitDetecion(sf::Vector2f t_position);

	// spawn new waves
	void SpawnNewWave();
	void spawnWave1();

	// non-character data members
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_health; // text used for message on screen
	sf::Text m_scoreText; // score used for performance
	sf::Texture m_backgroundTexture; // texture used for sfml logo
	sf::Sprite m_backgroundSprite; // sprite used for background
	bool m_exitGame; // control exiting game

	short m_waveCounter = 0;
	int m_timeCounter = 1;
	int m_score = 0;
	GameState m_mode = GameState::gameScreen;

	unsigned short m_numberStabbers = 7; // number of Stabbers in game (for for loops)
	unsigned short m_numberThrowers = 5; // number of Throwers in game

	short m_killedStabbers = 0; // number of stabbers killed
	short m_killedThrowers = 0; // number of throwers killed 

	// object related data members
	EnemyType m_enemy = EnemyType::stabber; // basic enemy type enum
	int m_animationCounter = 0; // counter to manage animation

	// objects
	Player m_player; // Player object
	Stabber m_stabberKobold[MAX_STABBERS]; // array of Stabber Kobolds
	Thrower m_throwerKobold[MAX_THROWERS]; // array of thrower Kobolds
	Javelin m_javelins[MAX_THROWERS]; // array of Javelins for throwers
	Arrow m_arrow; // arrow object
	EndGameScreen m_endScreen; // end of game screen as object
	
};

#endif // !GAME_HPP

