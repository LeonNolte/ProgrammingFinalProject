/// <summary>
/// Leon Nolte
/// C00263935
/// ------------------------------------------------------
/// Enemy type "Stabber:" follows the player in a zig-zag pattern 
/// Stabs player upon touching them
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Stabber
{
public:

	Stabber();
	sf::Sprite getSprite();
	void setPosition(sf::Vector2f t_position);

private:

	sf::Vector2f m_stabberLocation;
	sf::Sprite m_stabberSprite;
	sf::Texture m_stabberTexture;
};

