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

class Thrower
{
public:

	Thrower();
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	float getSpeed();
	void setPosition(sf::Vector2f t_newPosition);
	bool Thrower::checkInRange(sf::Vector2f t_playerPosition);
	sf::Vector2f throwJavelin(sf::Vector2f t_playerPosition, Javelin& t_javelin);

	const float THROWER_MOVE_SPEED = 1.5f;

private:

	sf::Vector2f m_throwerLocation; // location of Thrower Kobold
	sf::Sprite m_throwerSprite; // sprite of Thrower Kobold
	sf::Texture m_throwerTexture; // texture of Thrower Kobold

};

