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
	// Status getStatus() { return m_stabberState; }; // gets state of thrower
	bool getAlive() { return m_alive; };

	bool isCountingUp();
	void die();

	// set functions
	void setPosition(sf::Vector2f t_newPosition);
	void setPosition(float t_x, float t_y);
	void setAlive(bool t_alive) { m_alive = t_alive; };

	const float STABBER_SPEED = 1.8f;
	const short DAMAGE = 10;

private:

	sf::Vector2f m_stabberLocation; // location of stabber
	sf::Sprite m_stabberSprite; // sprite of stabber
	sf::Texture m_stabberTexture; // texture of stabber

	int m_zigZagCounter; // counts up and down to produce zig zag movement
	bool m_countingUp = true; // for zig zag counter, true when counting up (move left while approaching player)

	// Status m_stabberState = Status::dead; // status variable of stabber
	bool m_alive = true;
	bool m_spawned = false; // true if kobold is in bound

};

