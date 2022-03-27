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

	// get functions
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	float getSpeed();
	int getZigZagCounter();
	bool getAlive() { return m_alive; };

	bool isCountingUp();
	void die();

	// set functions
	void setPosition(sf::Vector2f t_newPosition);
	void setPosition(float t_x, float t_y);
	void setAlive(bool t_alive) { m_alive = t_alive; };

	const float STABBER_SPEED = 1.5f;
	const short DAMAGE = 10;


private:

	sf::Vector2f m_stabberLocation;
	sf::Sprite m_stabberSprite;
	sf::Texture m_stabberTexture;

	int m_zigZagCounter;
	bool m_countingUp = true;
	bool m_alive = true;

};

