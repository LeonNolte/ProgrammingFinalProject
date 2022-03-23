/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Enemy type "Thrower:" Walks up to the player up until a vertain range and throws a spear, then retreats in ZigZagPattern
/// </summary>


#include "Thrower.h"

Thrower::Thrower()
{
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
	return THROWER_MOVE_SPEED;
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
/// checks if Thrower is in range to throw Javelin
/// throws Javelin when in range
/// </summary>
/// <returns> true when in range/ false when not in range </returns>
bool Thrower::checkInRange(sf::Vector2f t_playerPosition)
{
	bool inRange = false;
	sf::Vector2f lineToPlayer; // line drawn from Kobold to player
	float range; // range at which Javelin is thrown

	lineToPlayer = m_throwerLocation - t_playerPosition;
	range = vectorLength(lineToPlayer);a

	if (range > vectorLength(lineToPlayer))
	{
		inRange = true;
	}

	return inRange;
}


/// <summary>
/// throw Javelin at player
/// gets line to player , turns it into unit vector and multiplies it with Javelin velocity
/// </summary>
/// <param name="t_playerPosition"> position of player </param>
/// <param name="t_javelin"> pointer at javelin object </param>
/// <returns> javelin trowing velocity </returns>
sf::Vector2f Thrower::throwJavelin(sf::Vector2f t_playerPosition, Javelin &t_javelin)
{
	sf::Vector2f lineToPlayer; // line drawn to player position
	sf::Vector2f newVelocity; // new velocity 

	lineToPlayer = m_throwerLocation - t_playerPosition;
	newVelocity = vectorUnitVector(lineToPlayer) * t_javelin.STANDARD_SPEED;

	t_javelin.setTraveling(true);

	return newVelocity;
}
