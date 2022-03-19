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
	m_zigZagCounter = -50 + rand() % 100;

	m_stabberLocation = { 10.0f, 10.0f };
	
	if (!m_stabberTexture.loadFromFile("ASSETS\\IMAGES\\Stabber.png"))
	{
		std::cout << "problem loading stabber texture" << std::endl;
	}

	m_stabberSprite.setTexture(m_stabberTexture);
	m_stabberSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_stabberSprite.setScale(3.0f, 3.0f);
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
/// gets speed of Stabber Kobold
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

	if (m_zigZagCounter > 50)
	{
		m_countingUp = !m_countingUp;
	}
	else if (m_zigZagCounter < -50)
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
