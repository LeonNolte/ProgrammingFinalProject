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
	setupObjects(); // construct game objects
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

	// key check in update for smoother controlls 
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

	stabberFollowPlayer();
	throwerFollowPlayer();
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

		if (index > NUMBER_THROWERS - 1)
		{
			continue;
		}
		else
		{
			m_window.draw(m_throwerKobold[index].getSprite());
		}
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
	sf::Vector2f stabberSpawn1{ 20.0f, 20.0f };
	sf::Vector2f stabberSpawn2{ 600.0f, 20.0f };
	sf::Vector2f throwerSpawn{ 700.0f, 70.0f };

	m_player.setPosition(100.0f, 100.0f);
	
	for (short index = 0; index < NUMBER_STABBERS; index++) // for now: one loop for throwers and stabbers
	{
		if (index % 2 == 0)
		{
			m_stabberKobold[index].setPosition(stabberSpawn1);
			stabberSpawn1.y += 200.0f;
		}
		if (index % 2 == 1)
		{
			m_stabberKobold[index].setPosition(stabberSpawn2);
			stabberSpawn2.y += 200.0f;
		}
		if (index > NUMBER_THROWERS - 1)
		{
			continue;
		}
		else
		{
			m_throwerKobold[index].setPosition(throwerSpawn);
			throwerSpawn.y += 150.0f;
		}
		
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
		newVelocity.y = m_player.PLAYER_SPEED;
		moveUp(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	case Direction::Down:
		newVelocity.y = m_player.PLAYER_SPEED;
		moveDown(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(0, 0, 32, 32));
		break;
	case Direction::Left:
		newVelocity.x = m_player.PLAYER_SPEED;
		moveLeft(newPosition, newVelocity);
		m_player.newTextureRect(sf::IntRect(64, 0, 32, 32));
		break;
	case Direction::Right:
		newVelocity.x = m_player.PLAYER_SPEED;
		moveRight(newPosition, newVelocity);
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
void Game::moveUp(sf::Vector2f &t_position, sf::Vector2f t_velocity)
{
	if (t_position.y >= 0.0f)
	{
		t_position.y -= t_velocity.y; // minus to move up
	}
}


/// <summary>
/// moves a game object position vector towards the bottom of the screen
/// checks boundaries
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> pointer to position vector </param>
/// <param name="t_velocity"> speed parameter </param>
void Game::moveDown(sf::Vector2f& t_position, sf::Vector2f t_velocity)
{
	if (t_position.y < WINDOW_HEIGHT - FIGURE_SIZE)
	{
		t_position.y += t_velocity.y;
	}
}


/// <summary>
/// moves a game object position vector towards the left side of the screen
/// checks boundaries
/// (does not involve change to sprite)
/// </summary>
/// <param name="t_position"> pointer to position vector </param>
/// <param name="t_velocity"> speed parameter </param>
void Game::moveLeft(sf::Vector2f& t_position, sf::Vector2f t_velocity)
{
	if (t_position.x > 0.0f)
	{
		t_position.x -= t_velocity.x;
	}
}


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


/// <summary>
/// function to make all stabbers follow the player
/// </summary>
void Game::stabberFollowPlayer()
{
	sf::Vector2f newVelocity; // new velocity of Kobold
	sf::Vector2f newLocation; // sets new location of stabber

	
	for (int index = 0; index < NUMBER_STABBERS; index++)
	{
		newLocation = m_stabberKobold[index].getPosition();

		
		// for following
		if (m_player.getPosition().x > m_stabberKobold[index].getPosition().x)
		{
			newVelocity.x = m_stabberKobold[index].getSpeed();
			moveRight(newLocation, newVelocity);
		}
		if (m_player.getPosition().x < m_stabberKobold[index].getPosition().x)
		{
			newVelocity.x = m_stabberKobold[index].getSpeed();
			moveLeft(newLocation, newVelocity);
		}

		if (m_player.getPosition().y > m_stabberKobold[index].getPosition().y)
		{
			newVelocity.y = m_stabberKobold[index].getSpeed();
			moveDown(newLocation, newVelocity);
		}
		if (m_player.getPosition().y < m_stabberKobold[index].getPosition().y)
		{
			newVelocity.y = m_stabberKobold[index].getSpeed();
			moveUp(newLocation, newVelocity);
		}

		enemyZigZag(newLocation, index, EnemyType::stabber);

		if (newLocation.y >= 0.0f && newLocation.x >= 0.0f && newLocation.x <= WINDOW_WIDTH - FIGURE_SIZE && newLocation.y <= WINDOW_WIDTH - FIGURE_SIZE)
		{
			// sets position of Kobold to new location
			m_stabberKobold[index].setPosition(newLocation);
		}
	}
}

/// <summary>
/// follow player function for thrower Kobolds
/// Follow the player up until certain distance, then hover until throwing their spears
/// </summary>
void Game::throwerFollowPlayer()
{
	sf::Vector2f newVelocity; // new velocity of thrower Kobold
	sf::Vector2f newLocation; // sets new location of thrower Kobold

	for (int index = 0; index < NUMBER_THROWERS; index++)
	{
		newLocation = m_throwerKobold[index].getPosition();

		// for following
		if (m_player.getPosition().x > m_throwerKobold[index].getPosition().x)
		{
			newVelocity.x = m_throwerKobold[index].getSpeed();
			moveRight(newLocation, newVelocity);
		}
		if (m_player.getPosition().x < m_throwerKobold[index].getPosition().x)
		{
			newVelocity.x = m_throwerKobold[index].getSpeed();
			moveLeft(newLocation, newVelocity);
		}
		if (m_player.getPosition().y > m_throwerKobold[index].getPosition().y)
		{
			newVelocity.y = m_throwerKobold[index].getSpeed();
			moveDown(newLocation, newVelocity);
		}
		if (m_player.getPosition().y < m_throwerKobold[index].getPosition().y)
		{
			newVelocity.y = m_throwerKobold[index].getSpeed();
			moveUp(newLocation, newVelocity);
		}

		
		if (getDistanceToPlayer(newLocation, index, EnemyType::thrower) > 300.0f)
		{
				// sets position of Kobold to new location
				m_throwerKobold[index].setPosition(newLocation);
		}

		
		if (getDistanceToPlayer(newLocation, index, EnemyType::thrower) < 200.0f) // if player gets too close
		{
			newVelocity *= 2.0f; // to negate previous movement

			// reverse movement to follow player
			if (newLocation.x >= 0.0f && newLocation.x <= WINDOW_WIDTH - FIGURE_SIZE) // basic bound check
			{
				if (newLocation.x > m_player.getPosition().x)
				{
					newLocation.x += newVelocity.x;
				}
				else
				{
					newLocation.x -= newVelocity.x;
				}
			}
			if (newLocation.y >= 0.0f && newLocation.y <= WINDOW_WIDTH - FIGURE_SIZE) // bound check y
			{
				if (newLocation.y > m_player.getPosition().y)
				{
					newLocation.y += newVelocity.y;
				}
				else
				{
					newLocation.y -= newVelocity.y;
				}
			}
				
			m_throwerKobold[index].setPosition(newLocation);
		}
	}
}

/// <summary>
/// gets distance between Kobold and player
/// </summary>
/// <param name="t_position"> position of Kobold </param>
/// <param name="t_arrayIndex"> array ID of Kobold </param>
/// <param name="t_enemy"> type of Kobold </param>
float Game::getDistanceToPlayer(sf::Vector2f& t_position, int t_arrayIndex, EnemyType t_enemy)
{
	sf::Vector2f lineToPlayer; // line from Kobold to player
	float distanceToPlayer = 0.0f; // distance to player sprite

	if (t_enemy == EnemyType::thrower)
	{
		lineToPlayer = m_player.getPosition() - m_throwerKobold[t_arrayIndex].getPosition();
	}
	else
	{
		lineToPlayer = m_player.getPosition() - m_stabberKobold[t_arrayIndex].getPosition();
	}

	distanceToPlayer = vectorLength(lineToPlayer);

	return distanceToPlayer;
}

/// <summary>
/// makes enemy walk in zig zag pattern
/// </summary>
/// <param name="t_position"> position of Kobold </param>
/// <param name="t_arrayIndex"> array ID of Kobold </param>
/// <param name="t_enemy"> type of Kobold </param>
void Game::enemyZigZag(sf::Vector2f &t_position, int t_arrayIndex, EnemyType t_enemy)
{
	sf::Vector2f lineToPlayer; // line drawn from stabber to player
	sf::Vector2f zigZagStep; // zig zag movement for next frame

	if (t_enemy == EnemyType::stabber)
	{
		// for zig zag
		lineToPlayer = (m_player.getPosition() - m_stabberKobold[t_arrayIndex].getPosition()); // draws line between stabber and player as vector

		if (m_stabberKobold[t_arrayIndex].getZigZagCounter() < 0)
		{
			zigZagStep = { -2.0f, -2.0f };
		}
		else
		{
			zigZagStep = { 2.0f, 2.0f };
		}
	}
	
	t_position += vectorRejection(zigZagStep, lineToPlayer); // rejects zig zag step from line to player
}


