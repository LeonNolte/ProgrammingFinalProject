/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Enemy type "Thrower:" Walks up to the player up until a vertain range and throws a spear, then retreats in ZigZagPattern
/// </summary>


#include "Thrower.h"

Thrower::Thrower()
{
	m_throwerLocation = { 200.0f, 10.0f };

	if (!m_throwerTexture.loadFromFile("ASSETS\\IMAGES\\Thrower.png"))
	{
		std::cout << "problem loading thrower texture" << std::endl;
	}

	m_throwerSprite.setTexture(m_throwerTexture);
	m_throwerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_throwerSprite.setScale(3.0f, 3.0f);
}

/// <summary>
/// gets sprite of stabber
/// </summary>
/// <returns> stabber sprite </returns>
sf::Sprite Thrower::getSprite()
{
	return m_throwerSprite;
}

/// <summary>
/// gets position of stabber
/// </summary>
/// <returns> position vector of stabber </returns>
sf::Vector2f Thrower::getPosition()
{
	return m_throwerLocation;
}

/// <summary>
/// gets speed of Stabber Kobold
/// </summary>
/// <returns> standard speed </returns>
float Thrower::getSpeed()
{
	return throwerStandardSpeed;
}

/// <summary>
/// sets position of Stabber Kobold
/// </summary>
void Thrower::setPosition(sf::Vector2f t_newPosition)
{
	m_throwerLocation = t_newPosition;
	m_throwerSprite.setPosition(t_newPosition);
}