/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Projectile Type "Javelin:" Gets thrown by Thrower Kobolds and has a certain firing range
/// </summary>

#include <SFML/Graphics.hpp>
#include "MyVector2.h"

#pragma once
class Javelin
{
public:
	Javelin();
	void setPosition(sf::Vector2f t_newPosition);
	void setPosition(float t_x, float t_y);
	sf::Vector2f getPosition();

	void setVelocity(sf::Vector2f t_newVelocity);
	sf::Vector2f getVelocity();

	void setTraveling(bool t_travelStatus);
	bool getTraveling();

	void setjavSpawn(sf::Vector2f t_spawn) { m_javSpawn = t_spawn; }; // sets spawn of javelin (location it was originally thrown from)
	sf::Vector2f getjavSpawn() { return m_javSpawn; }; // returns spawn location of Javelin

	void travel();

	sf::CircleShape getSprite() { return m_javHitBox; }; // hit box as stand-in for sprite

	const float STANDARD_SPEED = 8.0f;
	const float JAVELIN_RANGE = 600.0f;

private:
	sf::CircleShape m_javHitBox;
	sf::Vector2f m_javVelocity;
	sf::Vector2f m_javSpawn;
	bool m_traveling = false;
};


