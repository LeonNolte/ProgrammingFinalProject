/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Player class: can move across the screen and shoot arrows 
/// </summary>

#include "Player.h"

/// <summary>
/// constructor for player class
/// </summary>
Player::Player()
{
	m_playerLocation = { 100.0, 100.0 };
	m_playerSprite.setPosition(m_playerLocation);

	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\ArcherSpritesheet.png"))
	{
		std::cout << "problem loading player texture" << std::endl;
	}

	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_playerSprite.setScale(4.0f, 4.0f);

	m_playerVelocity = { 0.0f, 0.0f };
}

sf::Vector2f Player::getPosition()
{
	return m_playerLocation;
}

/// <summary>
/// to set position of player using two floats
/// </summary>
/// <param name="t_x"> x of position </param>
/// <param name="t_y"> y of position </param>
void Player::setPosition(float t_x, float t_y)
{
	m_playerLocation = { t_x, t_y };
	m_playerSprite.setPosition(t_x, t_y);
}

/// <summary>
/// to set position of player using sf::Vector2f
/// </summary>
/// <param name="t_position"> position vector </param>
void Player::setPosition(sf::Vector2f t_newPosition)
{
	m_playerLocation = t_newPosition;
	m_playerSprite.setPosition(t_newPosition);
}

/// <summary>
/// sets new player velocity
/// </summary>
/// <param name="t_x"> new x parameter </param>
/// <param name="t_y"> new y parameter </param>
void Player::setVelocity(float t_x, float t_y)
{
	m_playerVelocity = { t_x, t_y };
}

/// <summary>
/// sets new player velocity
/// </summary>
/// <param name="t_newVelocity"> new player velocity </param>
void Player::setVelocity(sf::Vector2f t_newVelocity)
{
	m_playerVelocity = t_newVelocity;
}

/// <summary>
/// to get player sprite
/// </summary>
/// <returns> sprite of player </returns>
sf::Sprite Player::getSprite()
{
	return m_playerSprite;
}

/// <summary>
/// sets new texture rectangle
/// </summary>
/// <param name="t_textureRect"> new texturebrectangle </param>
void Player::newTextureRect(sf::IntRect t_textureRect)
{
	m_playerSprite.setTextureRect(t_textureRect);
}

sf::Vector2f Player::getVelocity()
{
	return m_playerVelocity;
}
