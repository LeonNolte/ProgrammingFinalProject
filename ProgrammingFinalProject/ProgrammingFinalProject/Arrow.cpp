/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Projectile Type "Arrow:" Gets fired by the player and has a certain firing range
/// </summary>

#include "Arrow.h"

/// <summary>
/// constructor
/// </summary>
Arrow::Arrow()
{
	m_arrowHitBox.setFillColor(sf::Color::Blue);
	m_arrowHitBox.setRadius(2.0f);
	m_arrowHitBox.setPosition(5.0f, 5.0f);
}

/// <summary>
/// sets position of arrowhead
/// </summary>
/// <param name="t_newPosition"> new position of arrowhead </param>
void Arrow::setPosition(sf::Vector2f t_newPosition)
{
	m_arrowHitBox.setPosition(t_newPosition);
}

/// <summary>
/// gets position of arrow head
/// </summary>
/// <returns> position vector of arrow head (hitbox) </returns>
sf::Vector2f Arrow::getPosition()
{
	return m_arrowHitBox.getPosition();
}

/// <summary>
/// sets velocity of arrow
/// </summary>
/// <param name="t_newVelocity"> new velocity of arrow </param>
void Arrow::setVelocity(sf::Vector2f t_newVelocity)
{
	m_arrowVelocity = t_newVelocity;
}

/// <summary>
/// gets current velocity of arrow
/// </summary>
/// <returns> velocity vector </returns>
sf::Vector2f Arrow::getVelocity()
{
	return m_arrowVelocity;
}
