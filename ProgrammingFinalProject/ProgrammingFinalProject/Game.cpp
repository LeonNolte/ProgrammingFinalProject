/// <summary>
/// Leon Nolte
/// C00263935
/// </summary>

#include "Game.h"

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
	setupObjects();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movePlayer(Direction::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movePlayer(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movePlayer(Direction::Down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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

	// stabberFollowPlayer();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player.getSprite());
	for (int index = 0; index < NUMBER_STABBERS; index++)
	{
		m_window.draw(m_stabberKobold[index].getSprite());
	}
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
	sf::Vector2f stabberSpawn{ 20.0f, 20.0f };

	m_player.setPosition(100.0f, 100.0f);
	
	for (short index = 0; index < NUMBER_STABBERS; index++)
	{
		m_stabberKobold[index].setPosition(stabberSpawn);
		stabberSpawn.y += 50.0f;
	}
}

/// <summary>
/// moves player in certain direction
/// diagonal movement is possible
/// </summary>
/// <param name="t_direction"> direction of movement </param>
void Game::movePlayer(Direction t_direction)
{
	sf::Vector2f newPosition = m_player.getPosition();
	sf::Vector2f newVelocity = m_player.getVelocity();
	
	switch (t_direction)
	{
	case Direction::Up:
		newVelocity.y = m_player.PLAYER_SPEED * -1.0f;
		moveVertical(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case Direction::Down:
		newVelocity.y = m_player.PLAYER_SPEED;
		moveVertical(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case Direction::Left:
		newVelocity.x = m_player.PLAYER_SPEED * -1.0f;
		moveHorizontal(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(64, 0, 32, 32));
		break;
	case Direction::Right:
		newVelocity.x = m_player.PLAYER_SPEED;
		moveHorizontal(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(96, 0, 32, 32));
		break;
	}
	
	m_player.setVelocity(newVelocity);
	m_player.setPosition(newPosition);

}

/// <summary>
/// moves game object position vector towards the top of the screen
/// checks boundaries
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> position of object </param>
/// <param name="t_speed"> speed parameter </param>
void Game::moveVertical(sf::Vector2f &t_position, sf::Vector2f t_velocity)
{
	if (t_position.y >= 0.0f && t_position.y <= WINDOW_HEIGHT - FIGURE_SIZE)
	{
		t_position.y += t_velocity.y;
	}
	else
	{
		t_position.y -= t_velocity.y;
	}
}

/*
/// <summary>
/// moves a game object position vector towards the bottom of the screen
/// checks boundaries
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> pointer to position vector </param>
/// <param name="t_speed"> speed parameter </param>
void Game::moveDown(sf::Vector2f& t_position, sf::Vector2f t_velocity)
{
	if (t_position.y < WINDOW_HEIGHT - FIGURE_SIZE)
	{
		t_position.y += t_velocity.y;
	}
}
*/

/// <summary>
/// moves a game object position vector towards the left side of the screen
/// checks boundaries
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> pointer to position vector </param>
/// <param name="t_speed"> speed parameter </param>
void Game::moveHorizontal(sf::Vector2f& t_position, sf::Vector2f t_velocity)
{
	if (t_position.x > 0.0f && t_position.x < WINDOW_WIDTH - FIGURE_SIZE)
	{
		t_position.x += t_velocity.x;
	}
	else
	{
		t_position.x -= t_velocity.x;
	}
}

/*
/// <summary>
/// moves a game object position vector towards the right side of the screen
/// checks boundary
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> pointer to position vector </param>
/// <param name="t_speed"> speed parameter </param>
void Game::moveRight(sf::Vector2f& t_position, sf::Vector2f t_velocity)
{
	if (t_position.x < WINDOW_WIDTH - FIGURE_SIZE)
	{
		t_position.x += t_velocity.x;
	}
}
*/

/// <summary>
/// function to make all stabbers follow the player
/// </summary>
void Game::stabberFollowPlayer()
{
	sf::Vector2f lineToPlayer; // line drawn from stabber to player
	sf::Vector2f stepTowardsPlayer; // movement for next frame
	sf::Vector2f newLocation; // sets new location of stabber

	for (int index = 0; index < NUMBER_STABBERS; index++)
	{
		newLocation = m_stabberKobold[index].getPosition();
		lineToPlayer = (m_player.getPosition() - m_stabberKobold[index].getPosition()) * 100.0f; // draws line between stabber and player as vector

		// projects standard velocity onto line to player
		stepTowardsPlayer = vectorRejection(m_stabberKobold[index].stabberStandardVelocity, lineToPlayer);

		m_stabberKobold[index].setVelocity(stepTowardsPlayer);

		moveHorizontal(newLocation, stepTowardsPlayer);
		moveVertical(newLocation, stepTowardsPlayer);

		m_stabberKobold[index].setPosition(newLocation);
	}
}


