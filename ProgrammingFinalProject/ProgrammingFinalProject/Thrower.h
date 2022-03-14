/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Enemy type "Stabber:" follows the player in a zig-zag pattern 
/// Stabs player upon touching them
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Thrower
{
public:

	Thrower();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getSpeed();
	void setPosition(sf::Vector2f t_newPosition);
	void setVelocity(sf::Vector2f t_newVelocity);

	const float throwerStandardSpeed = 1.5f;

private:

	sf::Vector2f m_throwerLocation;
	sf::Vector2f m_throwerVelocity;
	sf::Sprite m_throwerSprite;
	sf::Texture m_throwerTexture;

};

