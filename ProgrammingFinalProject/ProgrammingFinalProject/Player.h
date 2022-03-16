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

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

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
	void newTextureRect(sf::IntRect t_textureRect);

	void initializeArrows();
	void shootArrow();

	const float PLAYER_SPEED = 2.5f;
	


private:
	sf::Vector2f m_playerLocation;
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerVelocity;

	Arrow m_arrows[10];
};