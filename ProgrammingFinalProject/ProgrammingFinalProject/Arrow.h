/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Projectile Type "Arrow:" Gets fired by the player and has a certain firing range
/// </summary>

#include <SFML/Graphics.hpp>

#pragma once
class Arrow
{
public:
	Arrow();
	void setPosition(sf::Vector2f t_newPosition);
	void setPosition(float t_x, float t_y);
	sf::Vector2f getPosition();

	void setVelocity(sf::Vector2f t_newVelocity);
	sf::Vector2f getVelocity();

	void setTraveling(bool t_travelStatus);
	bool getTraveling();

	sf::CircleShape getSprite() { return m_arrowHitBox; }; // hit box as stand-in for sprite

	const float STANDARD_SPEED = 10.0f;

private:
	sf::CircleShape m_arrowHitBox;
	sf::Vector2f m_arrowVelocity;
	bool m_traveling = false;
};

