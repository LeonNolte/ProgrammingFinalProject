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
	m_throwerVelocity = { 0.0f, 0.0f };

	if (!m_throwerTexture.loadFromFile("ASSETS\\IMAGES\\ArcherSpritesheet.png"))
	{
		std::cout << "problem loading player texture" << std::endl;
	}

	m_throwerSprite.setTexture(m_throwerTexture);
	m_throwerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_throwerSprite.setScale(4.0f, 4.0f);
	m_throwerSprite.setColor(sf::Color::Red);
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
/// gets stabber velocity
/// </summary>
/// <returns></returns>
sf::Vector2f Thrower::getVelocity()
{
	return m_throwerVelocity;
}

/// <summary>
/// gets velocity of Stabber Kobold
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

/// <summary>
/// sets new velocity to stabber Kobold
/// </summary>
/// <param name="t_newVelocity"> new velocity for stabber </param>
void Thrower::setVelocity(sf::Vector2f t_newVelocity)
{
	m_throwerVelocity = t_newVelocity;
}