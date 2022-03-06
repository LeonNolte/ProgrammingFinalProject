#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	void setPosition(float t_x, float t_y);
	void setPosition(sf::Vector2f t_position);
	sf::Sprite getSprite();


private:
	sf::Vector2f m_playerLocation;
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
};