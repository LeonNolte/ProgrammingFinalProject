/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Player class: can move across the screen and shoot arrows 
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

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

	const float PLAYER_SPEED = 5.0f;
	


private:
	sf::Vector2f m_playerLocation;
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerVelocity;
};