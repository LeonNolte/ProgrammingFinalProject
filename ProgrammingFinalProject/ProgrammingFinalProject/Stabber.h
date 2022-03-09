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
#include <random>
#include <time.h>

class Stabber
{
public:

	Stabber();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getSpeed();
	int getZigZagCounter();
	bool isCountingUp();
	void setPosition(sf::Vector2f t_newPosition);
	void setVelocity(sf::Vector2f t_newVelocity);

	const float stabberStandardSpeed = 1.0f;

private:

	sf::Vector2f m_stabberLocation;
	sf::Vector2f m_stabberVelocity;
	sf::Sprite m_stabberSprite;
	sf::Texture m_stabberTexture;

	int m_zigZagCounter = 0;
	bool m_countingUp = true;

};

