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
#include "Javelin.h"
#include <random>

class Thrower
{
public:

	Thrower();

	// get functions
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	float getSpeed();
	bool getFollowing() { return m_following; }; // gets following status
	bool getAlive() { return m_alive; }; // gets alive status

	short incrementWaitCounter();

	// set functions
	void setPosition(sf::Vector2f t_newPosition);
	void setFollowing(bool t_following) { m_following = t_following; }; // sets new following status
	void setAlive(bool t_alive) { m_alive = t_alive; }; // sets new alive status

	bool checkInRange(sf::Vector2f t_playerPosition);
	void throwJavelin(sf::Vector2f t_playerPosition, Javelin& t_javelin);
	void die();

	const float THROWER_MOVE_SPEED = 1.5f;
	const short DAMAGE = 15;

private:

	sf::Vector2f m_throwerLocation; // location of Thrower Kobold
	sf::Sprite m_throwerSprite; // sprite of Thrower Kobold
	sf::Texture m_throwerTexture; // texture of Thrower Kobold

	bool m_following = true; // true when following player before throwing javelin
	bool m_alive = true;

	short m_waitCounter = 0; // makes throwers wait when in range

};

