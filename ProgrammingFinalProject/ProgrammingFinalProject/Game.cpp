/// <summary>
/// Leon Nolte
/// C00263935
/// </summary>

#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32U }, "Kobold Mayhem" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::W == t_event.key.code)
	{
		movePlayer(Direction::Up);
	}
	if (sf::Keyboard::A == t_event.key.code)
	{
		movePlayer(Direction::Left);
	}
	if (sf::Keyboard::S == t_event.key.code)
	{
		movePlayer(Direction::Down);
	}
	if (sf::Keyboard::D == t_event.key.code)
	{
		movePlayer(Direction::Right);
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player.getSprite());
	m_window.display();
	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_score.setFont(m_ArialBlackfont);
	m_score.setString("SFML Game");
	m_score.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_score.setPosition(40.0f, 40.0f);
	m_score.setCharacterSize(30U);
	m_score.setFillColor(sf::Color::Black);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	
}

/// <summary>
/// to set up game objects
/// includes: Player
/// </summary>
void Game::setupObjects()
{
	m_player.setPosition(100.0f, 100.0f);
}

/// <summary>
/// moves player in certain direction
/// </summary>
/// <param name="t_direction"> direction of movement</param>
void Game::movePlayer(Direction t_direction)
{
	sf::Vector2f newPosition = m_player.getPosition();

	switch (t_direction)
	{
	case Direction::Up:
		moveUp(newPosition, m_player.getSprite(), m_player.getSpeed());
		m_player.newTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case Direction::Down:
		moveDown(newPosition, m_player.getSprite(), m_player.getSpeed());
		m_player.newTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case Direction::Left:
		newPosition.x -= m_player.getSpeed();
		break;
	case Direction::Right:
		newPosition.x += m_player.getSpeed();
		break;
	}

	m_player.setPosition(newPosition);

}

/// <summary>
/// moves game object up
/// </summary>
/// <param name="t_position"> position of object </param>
/// <param name="t_sprite"> object sprite </param>
void Game::moveUp(sf::Vector2f &t_position, sf::Sprite &t_sprite, float t_speed)
{
	sf::Vector2f newPosition = t_position;

	if (t_position.y > 0.0f)
	{
		newPosition.y -= t_speed;
		t_sprite.setPosition(newPosition);
		t_position = newPosition;
	}
}

void Game::moveDown(sf::Vector2f& t_position, sf::Sprite& t_sprite, float t_speed)
{
	sf::Vector2f newPosition = t_position;

	if (t_position.y < WINDOW_HEIGHT - FIGURE_SIZE)
	{
		newPosition.y += t_speed;
		t_sprite.setPosition(newPosition);
		t_position = newPosition;
	}
}
