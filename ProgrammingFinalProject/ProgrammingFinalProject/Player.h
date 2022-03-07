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
	void setPosition(float t_x, float t_y);
	void setPosition(sf::Vector2f t_position);

	sf::Sprite getSprite();
	void newTextureRect(sf::IntRect t_textureRect);
	float getSpeed();


private:
	sf::Vector2f m_playerLocation;
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	float m_speed;
};