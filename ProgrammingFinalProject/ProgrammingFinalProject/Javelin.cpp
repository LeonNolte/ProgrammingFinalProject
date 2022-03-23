/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Projectile Type "Javelin:" Gets thrown by Thrower Kobolds

#include "Javelin.h"

/// <summary>
/// constructor
/// </summary>
Javelin::Javelin()
{
	m_javHitBox.setFillColor(sf::Color::Yellow);
	m_javHitBox.setRadius(5.0f);
	m_javHitBox.setPosition(5.0f, 5.0f);
}

/// <summary>
/// sets position of arrowhead
/// </summary>
/// <param name="t_newPosition"> new position of arrowhead </param>
void Javelin::setPosition(sf::Vector2f t_newPosition)
{
	m_javHitBox.setPosition(t_newPosition);
}

void Javelin::setPosition(float t_x, float t_y)
{
	m_javHitBox.setPosition(t_x, t_y);
}

/// <summary>
/// gets position of arrow head
/// </summary>
/// <returns> position vector of arrow head (hitbox) </returns>
sf::Vector2f Javelin::getPosition()
{
	return m_javHitBox.getPosition();
}

/// <summary>
/// sets velocity of arrow
/// </summary>
/// <param name="t_newVelocity"> new velocity of arrow </param>
void Javelin::setVelocity(sf::Vector2f t_newVelocity)
{
	m_javVelocity = t_newVelocity;
}

/// <summary>
/// gets current velocity of arrow
/// </summary>
/// <returns> velocity vector </returns>
sf::Vector2f Javelin::getVelocity()
{
	return m_javVelocity;
}

/// <summary>
/// sets new status of arrow
/// </summary>
/// <param name="t_travelStatus"> new travel status </param>
void Javelin::setTraveling(bool t_travelStatus)
{
	m_traveling = t_travelStatus;
}

/// <summary>
/// gets status of arrow
/// </summary>
/// <returns> true if traveling, false if not traveling</returns>
bool Javelin::getTraveling()
{
	return m_traveling;
}

/// <summary>
/// moves Javelin
/// </summary>
void Javelin::travel()
{
	sf::Vector2f lineToSpawn = m_javHitBox.getPosition() - m_javSpawn; // sets up line to where the Javelin was thrown from
	float rangeCheck = vectorLength(lineToSpawn); // float to check the distenace traveled

	if (rangeCheck < JAVELIN_RANGE)
	{
		m_javHitBox.setPosition(m_javHitBox.getPosition() + m_javVelocity);
	}
	else
	{
		setTraveling(false);
	}
}
