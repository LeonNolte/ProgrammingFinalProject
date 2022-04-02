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
#include "Globals.h"



class Thrower
{
public:

	Thrower();

	// get functions
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	float getSpeed();
	Status getStatus() { return m_throwerState; }; // gets state of thrower

	short incrementWaitCounter();

	// set functions
	void setPosition(sf::Vector2f t_newPosition);
	void setStatus(Status t_newStatus) { m_throwerState = t_newStatus; }; // assigns new status to thrower
	void setSprite(sf::Sprite t_newSprite) { m_throwerSprite = t_newSprite; }; // sets new sprite

	bool checkInRange(sf::Vector2f t_playerPosition);
	void throwJavelin(sf::Vector2f t_playerPosition, Javelin& t_javelin);
	void die();

	const float THROWER_MOVE_SPEED = 1.5f;
	const short DAMAGE = 25;

private:

	sf::Vector2f m_throwerLocation; // location of Thrower Kobold
	sf::Sprite m_throwerSprite; // sprite of Thrower Kobold
	sf::Texture m_throwerTexture; // texture of Thrower Kobold

	Status m_throwerState = Status::entering; // status of thrower kobold

	short m_waitCounter = 0; // makes throwers wait when in range

};

