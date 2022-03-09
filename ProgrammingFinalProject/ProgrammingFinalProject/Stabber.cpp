/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Enemy type "Stabber:" follows the player in a zig-zag pattern 
/// Stabs player upon touching them
/// </summary>

#include "Stabber.h"

Stabber::Stabber()
{
	std::srand(static_cast<unsigned>(time(nullptr)));

	m_zigZagCounter = -59 +	std::rand() % 120;

	m_stabberLocation = { 10.0f, 10.0f };
	m_stabberVelocity = { 0.0f, 0.0f };
	
	if (!m_stabberTexture.loadFromFile("ASSETS\\IMAGES\\ArcherSpritesheet.png"))
	{
		std::cout << "problem loading player texture" << std::endl;
	}

	m_stabberSprite.setTexture(m_stabberTexture);
	m_stabberSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_stabberSprite.setScale(4.0f, 4.0f);
	m_stabberSprite.setColor(sf::Color::Yellow);
}

/// <summary>
/// gets sprite of stabber
/// </summary>
/// <returns> stabber sprite </returns>
sf::Sprite Stabber::getSprite()
{
	return m_stabberSprite;
}

/// <summary>
/// gets position of stabber
/// </summary>
/// <returns> position vector of stabber </returns>
sf::Vector2f Stabber::getPosition()
{
	return m_stabberLocation;
}

/// <summary>
/// gets stabber velocity
/// </summary>
/// <returns></returns>
sf::Vector2f Stabber::getVelocity()
{
	return m_stabberVelocity;
}

/// <summary>
/// gets velocity of Stabber Kobold
/// </summary>
/// <returns> standard speed </returns>
float Stabber::getSpeed()
{
	return stabberStandardSpeed;
}

/// <summary>
/// gets Zig Zag Counter and counts it up
/// </summary>
/// <returns> zig zag counter </returns>
int Stabber::getZigZagCounter()
{
	if (m_countingUp)
	{
		m_zigZagCounter++;
	}
	else
	{
		m_zigZagCounter--;
	}

	if (m_zigZagCounter > 60)
	{
		m_countingUp = !m_countingUp;
	}
	else if (m_zigZagCounter < -60)
	{
		m_countingUp = !m_countingUp;
	}

	return m_zigZagCounter;
}

/// <summary>
/// gets counting status
/// </summary>
/// <returns></returns>
bool Stabber::isCountingUp()
{
	return m_countingUp;
}

/// <summary>
/// sets position of Stabber Kobold
/// </summary>
void Stabber::setPosition(sf::Vector2f t_newPosition)
{
	m_stabberLocation = t_newPosition;
	m_stabberSprite.setPosition(t_newPosition);
}

/// <summary>
/// sets new velocity to stabber Kobold
/// </summary>
/// <param name="t_newVelocity"> new velocity for stabber </param>
void Stabber::setVelocity(sf::Vector2f t_newVelocity)
{
	m_stabberVelocity = t_newVelocity;
}
