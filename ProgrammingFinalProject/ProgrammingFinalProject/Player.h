/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Player class: can move across the screen and shoot arrows 
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Arrow.h"
#include "Globals.h"

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

const int NUMBER_ARROWS = 10;

class Player
{
public:
	Player();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();

	void setPosition(float t_x, float t_y);
	void setPosition(sf::Vector2f t_newPosition);

	void setVelocity(float t_x, float t_y);
	void setVelocity(sf::Vector2f t_newVelocity);

	sf::Sprite getSprite();
	void setSprite(sf::Sprite t_newSprite) { m_playerSprite = t_newSprite; };

	short getHealth() { return m_playerHealth; }; // gets player health
	void setHealth(short t_health) { m_playerHealth = t_health; }; // sets player healths

	void newTextureRect(sf::IntRect t_textureRect);

	void initializeArrows();
	void shootArrow(Arrow& t_arrow, sf::Vector2i t_direction);

	void takeDamage(short t_damage);

	const float PLAYER_SPEED = 2.5f;
	const sf::Vector2f PLAYER_SPAWN = { WINDOW_WIDTH / 2.0f, 500.0f };

	
private:
	sf::Vector2f m_playerLocation;
	sf::Vector2f m_playerCenterLocation; 
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerVelocity;

	short m_playerHealth;

};