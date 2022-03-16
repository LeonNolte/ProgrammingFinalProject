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
	sf::Vector2f getPosition();
	void setVelocity(sf::Vector2f t_newVelocity);
	sf::Vector2f getVelocity();

private:
	sf::CircleShape m_arrowHitBox;
	sf::Vector2f m_arrowVelocity;

};

