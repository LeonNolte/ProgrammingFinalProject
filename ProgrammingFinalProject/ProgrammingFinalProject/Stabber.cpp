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
	m_stabberLocation = { 10.0f, 10.0f };
	
	if (!m_stabberTexture.loadFromFile("ASSETS\\IMAGES\\ArcherSpritesheet.png"))
	{
		std::cout << "problem loading player texture" << std::endl;
	}

	m_stabberSprite.setTexture(m_stabberTexture);
	m_stabberSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_stabberSprite.setScale(4.0f, 4.0f);
	m_stabberSprite.setColor(sf::Color::Yellow);
}

sf::Sprite Stabber::getSprite()
{
	return m_stabberSprite;
}

/// <summary>
/// sets position of Stabber Kobold
/// </summary>
void Stabber::setPosition(sf::Vector2f t_position)
{
	m_stabberLocation = t_position;
	m_stabberSprite.setPosition(t_position);
}
