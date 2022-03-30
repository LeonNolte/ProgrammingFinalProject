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
		if (sf::Event::MouseButtonReleased == newEvent.type) // user pressed mouse button
		{
			processMouseReleases(newEvent);
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
/// deals with mouse clicks from user
/// </summary>
/// <param name="t_event"> mouse click event </param>
void Game::processMouseClikcs(sf::Event t_event)
{
	// curently empty, used for extra functionality arrow shot
}

/// <summary>
/// deal with mouse releases from user
/// </summary>
/// <param name="t_event"> mouse release revent </param>
void Game::processMouseReleases(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.key.code)
	{
		m_player.shootArrow(m_arrow, sf::Mouse::getPosition(m_window));
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

	updatePlayer();

	m_animationCounter++;

	updateEnemies();

	if (m_arrow.getTraveling() == true)
	{
		updateArrow();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backgroundSprite);
	m_window.draw(m_player.getSprite());

	for (int index = 0; index < NUMBER_STABBERS; index++)
	{
		if (m_stabberKobold[index].getStatus() != Status::dead)
		{
			m_window.draw(m_stabberKobold[index].getSprite());
		}
		
		if (index > NUMBER_THROWERS - 1)
		{
			continue;
		}
		else
		{
			if (m_throwerKobold[index].getStatus() != Status::dead)
			{
				m_window.draw(m_throwerKobold[index].getSprite());
			}
			if (m_javelins[index].getTraveling() == true)
			{
				m_window.draw(m_javelins[index].getSprite());
			}			
		}
	}

	if (m_arrow.getTraveling() == true)
	{
		m_window.draw(m_arrow.getSprite());
	}

	m_window.draw(m_health);
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
	m_health.setFont(m_ArialBlackfont);
	m_health.setString(std::to_string(m_player.getHealth()));
	m_health.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_health.setPosition(40.0f, 40.0f);
	m_health.setCharacterSize(30U);
	m_health.setFillColor(sf::Color::Black);
	m_health.setOutlineColor(sf::Color::White);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\Background_Day.png"))
	{
		std::cout << "problem loading background texture" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(3.0f, 3.0f);
	m_backgroundSprite.setPosition(0.0f, 0.0f);
}

/// <summary>
/// to set up game objects
/// includes: Player
/// </summary>
void Game::setupObjects()
{
	spawnWave1();
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
	sf::Sprite tempSprite = m_player.getSprite();
	
	switch (t_direction)
	{
	case Direction::Up:
		newVelocity.y = m_player.PLAYER_SPEED;
		moveUp(newPosition, newVelocity);
		animateCharacter(tempSprite, Direction::Up);
		break;
	case Direction::Down:
		newVelocity.y = m_player.PLAYER_SPEED;
		moveDown(newPosition, newVelocity);
		animateCharacter(tempSprite, Direction::Down);
		break;
	case Direction::Left:
		newVelocity.x = m_player.PLAYER_SPEED;
		moveLeft(newPosition, newVelocity);
		animateCharacter(tempSprite, Direction::Left);
		break;
	case Direction::Right:
		newVelocity.x = m_player.PLAYER_SPEED;
		moveRight(newPosition, newVelocity);
		animateCharacter(tempSprite, Direction::Right);
		break;
	}

	m_player.setSprite(tempSprite);
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
///  update player function
/// </summary>
void Game::updatePlayer()
{
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

	m_health.setString(std::to_string(m_player.getHealth()));

}

/// <summary>
/// function to make all stabbers follow the player
/// </summary>
void Game::updateStabbers()
{
	sf::Vector2f newVelocity; // new velocity of Kobold
	sf::Vector2f newLocation; // sets new location of stabber
	sf::Vector2f oldLocation; // to reset location for bound check
	
	for (int index = 0; index < NUMBER_STABBERS; index++)
	{
		if (m_stabberKobold[index].getStatus() == Status::following) // only checks when alive
		{
			newLocation = m_stabberKobold[index].getPosition();
			oldLocation = newLocation;

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

			// call zig-zag function
			enemyZigZag(newLocation, index);

			if (stabberhitDetection(m_stabberKobold[index].getSprite()) == true)
			{
				if (newLocation.x < m_player.getSprite().getPosition().x)
				{
					newLocation.x -= 35.0f;
				}
				else
				{
					newLocation.x += 35.0f;
				}
				m_player.takeDamage(m_stabberKobold->DAMAGE);
			}

			// sets position of Kobold to new location
			if (newLocation.x <= 0.0f || newLocation.x >= WINDOW_WIDTH - FIGURE_SIZE) // when out of bounds horizontally
			{
				m_stabberKobold[index].setPosition(oldLocation.x, newLocation.y);
			}
			else if (newLocation.y <= 0.0f || newLocation.y >= WINDOW_HEIGHT - FIGURE_SIZE) // when out of bounds vertically
			{
				m_stabberKobold[index].setPosition(newLocation.x, oldLocation.y);
			}
			else // within bounds movement
			{
				m_stabberKobold[index].setPosition(newLocation);
			}
		}
		else if (m_stabberKobold[index].getStatus() == Status::entering)
		{
			stabberEnter(index);
		}
	}
}

/// <summary>
/// follow player function for thrower Kobolds
/// Follow the player up until certain distance, then hover until throwing their spears
/// </summary>
void Game::updateThrowers()
{
	sf::Vector2f newVelocity = { m_throwerKobold[0].getSpeed(), m_throwerKobold[0].getSpeed() }; // new velocity of thrower Kobold
	sf::Vector2f newLocation; // sets new location of thrower Kobold
	
	for (int index = 0; index < NUMBER_THROWERS; index++)
	{
		if (m_throwerKobold[index].getStatus() != Status::dead) // only updates if Kobold is alive
		{
			newLocation = m_throwerKobold[index].getPosition();
			if (m_throwerKobold[index].getStatus() == Status::following) // follows player when true
			{
				// for following
				if (m_player.getPosition().x > m_throwerKobold[index].getPosition().x)
				{
					moveRight(newLocation, newVelocity);
				}
				if (m_player.getPosition().x < m_throwerKobold[index].getPosition().x)
				{
					moveLeft(newLocation, newVelocity);
				}
				if (m_player.getPosition().y > m_throwerKobold[index].getPosition().y)
				{
					moveDown(newLocation, newVelocity);
				}
				if (m_player.getPosition().y < m_throwerKobold[index].getPosition().y)
				{
					moveUp(newLocation, newVelocity);
				}

				// keeps distance from player
				throwerKeepDistance(newVelocity, newLocation, index);

				// check if in range to throw Javelin
				if (m_throwerKobold[index].checkInRange(m_player.getPosition()) == true)
				{
					if (m_javelins[index].getTraveling() == false) // throws Javelin only when it isn't traveling
					{
						if (m_throwerKobold[index].incrementWaitCounter() > 100) // throws Javelin after delay
						{
							m_throwerKobold[index].throwJavelin(m_player.getPosition(), m_javelins[index]);
						}
					}
				}

				// adjusts position of Kobold to keep distance/run away
				m_throwerKobold[index].setPosition(newLocation);
			}
			else if (m_throwerKobold[index].getStatus() == Status::fleeing) // runs away when javelin is thrown
			{
				newVelocity = { 0.8f, 0.8f };
				throwerRunAway(newVelocity, newLocation);
				m_throwerKobold[index].setPosition(newLocation);
			}
			else if (m_throwerKobold[index].getStatus() == Status::entering)
			{
				throwerEnter(index);
			}
		}
		
		// check if Javelin hit player after being thrown
		if (m_javelins[index].getTraveling() == true)
		{
			updateJavelin(m_javelins[index]);
		}
	}
}

/// <summary>
/// makes thrower keep distance to player
/// </summary>
/// <param name="t_velocity"> pointer to velocity of Kobold </param>
/// <param name="t_location"> pointer to location of Kobold </param>
/// <param name="index"> index of Kobold </param>
void Game::throwerKeepDistance(sf::Vector2f &t_velocity, sf::Vector2f &t_location, int index)
{
	if (getDistanceToPlayer(t_location, index, EnemyType::thrower) < 250.0f) // if player gets too close
	{
		t_velocity *= 2.0f; // to negate previous Kobold movement

		// reverse movement to follow player
		if (t_location.x >= 0.0f && t_location.x <= WINDOW_WIDTH - FIGURE_SIZE) // basic bound check x
		{
			if (t_location.x > m_player.getPosition().x)
			{
				t_location.x += t_velocity.x;
			}
			else
			{
				t_location.x -= t_velocity.x;
			}
		}
		if (t_location.y >= 0.0f && t_location.y <= WINDOW_HEIGHT - FIGURE_SIZE) // bound check y
		{
			if (t_location.y > m_player.getPosition().y)
			{
				t_location.y += t_velocity.y;
			}
			else
			{
				t_location.y -= t_velocity.y;
			}
		}
	}
}

/// <summary>
/// makes thrower run away
/// </summary>
void Game::throwerRunAway(sf::Vector2f& t_velocity, sf::Vector2f& t_location)
{
	// reverse movement to run away player
	if (t_location.x > m_player.getPosition().x)
	{
		t_location.x += t_velocity.x;
	}
	else
	{
		t_location.x -= t_velocity.x;
	}
	
	if (t_location.y > m_player.getPosition().y)
	{
		t_location.y += t_velocity.y;
	}
	else
	{
		t_location.y -= t_velocity.y;
	}
}


/// <summary>
/// makes thrower enter the playing field
/// </summary>
/// <param name="t_index"> index of thrower </param>
void Game::throwerEnter(short t_index)
{
	sf::Vector2f velocity{ m_throwerKobold->THROWER_MOVE_SPEED, m_throwerKobold->THROWER_MOVE_SPEED };
	sf::Vector2f location = m_throwerKobold[t_index].getPosition();
	
	// runs towards player from beyond the screen
	if (location.x > m_player.getPosition().x)
	{
		location.x -= velocity.x;
	}
	else
	{
		location.x += velocity.x;
	}

	if (location.y > m_player.getPosition().y)
	{
		location.y -= velocity.y;
	}
	else
	{
		location.y += velocity.y;
	}

	if ((location.x > 0.0f && location.y > 0.0f) && (location.x < WINDOW_WIDTH - 96.0f && location.y < WINDOW_HEIGHT - 96.0f))
	{
		m_throwerKobold[t_index].setStatus(Status::following);
	}

	m_throwerKobold[t_index].setPosition(location);
}

/// <summary>
/// stabber
/// </summary>
/// <param name="t_index"></param>
void Game::stabberEnter(short t_index)
{
	sf::Vector2f velocity{ m_stabberKobold->STABBER_SPEED, m_stabberKobold->STABBER_SPEED };
	sf::Vector2f location = m_stabberKobold[t_index].getPosition();

	// runs towards player from beyond the screen
	if (location.x > m_player.getPosition().x)
	{
		location.x -= velocity.x;
	}
	else
	{
		location.x += velocity.x;
	}

	if (location.y > m_player.getPosition().y)
	{
		location.y -= velocity.y;
	}
	else
	{
		location.y += velocity.y;
	}

	if ((location.x > 0.0f && location.y > 0.0f) && (location.x < WINDOW_WIDTH - 96.0f && location.y < WINDOW_HEIGHT - 96.0f))
	{
		m_stabberKobold[t_index].setStatus(Status::following);
	}

	m_stabberKobold[t_index].setPosition(location);
}

/// <summary>
/// checks if thrower gets out of bounds and despawns
/// </summary>
bool Game::checkDespawnThrower(sf::Vector2f t_location)
{
	bool leftBounds = false;

	// reverse movement to follow player
	if (t_location.x + FIGURE_SIZE <= 0.0f || t_location.x >= WINDOW_WIDTH || t_location.y + FIGURE_SIZE <= 0.0f || t_location.y >= WINDOW_HEIGHT) // beyond bound check
	{
		leftBounds = true;
	}

	return leftBounds;
}

/// <summary>
/// adjusts standard hitbox
/// </summary>
/// <param name="t_hitbox"> hitbox to be adjusted </param>
/// <param name="t_width"> width of new hitbox </param>
/// <param name="t_height"> t_height of new hitbox </param>
void Game::adjustHitbox(sf::FloatRect &t_hitbox, float t_width, float t_height)
{
	float newLeft = (96.0f - t_width) / 2.0f;
	float newTop = (96.0f - t_height) / 2.0f;

	t_hitbox.left += newLeft;
	t_hitbox.width = t_width;
	t_hitbox.height = t_height;
	t_hitbox.top += newTop;
}

/// <summary>
/// updates enemies and their projectiles
/// </summary>
void Game::updateEnemies()
{
	updateStabbers();
	updateThrowers();

	for (int index = 0; index < NUMBER_THROWERS; index++) // updates thrown javelins
	{
		if (m_javelins[index].getTraveling() == true)
		{
			m_javelins[index].travel();
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
void Game::enemyZigZag(sf::Vector2f &t_position, int t_arrayIndex)
{
	sf::Vector2f lineToPlayer; // line drawn from stabber to player
	sf::Vector2f zigZagStep; // zig zag movement for next frame

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

	t_position += vectorRejection(zigZagStep, lineToPlayer); // rejects zig zag step from line to player
}

/// <summary>
/// animates a character sprite the size of 32x32
/// </summary>
/// <param name="t_sprite"> sprite of character </param>
/// <param name="t_texture"> texture of character </param>
void Game::animateCharacter(sf::Sprite& t_sprite, Direction t_movementDirection)
{
	if (t_movementDirection == Direction::Down)
	{
		if (m_animationCounter < 8)
		{
			t_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
		}
		else if (m_animationCounter < 16)
		{
			t_sprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
		}
		else if (m_animationCounter < 24)
		{
			t_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
		}
		else if (m_animationCounter < 32)
		{
			t_sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
		}
	}

	if (t_movementDirection == Direction::Up)
	{
		if (m_animationCounter < 8)
		{
			t_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
		}
		else if (m_animationCounter < 16)
		{
			t_sprite.setTextureRect(sf::IntRect(32, 32, 32, 32));
		}
		else if (m_animationCounter < 24)
		{
			t_sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
		}
		else if (m_animationCounter < 32)
		{
			t_sprite.setTextureRect(sf::IntRect(32, 96, 32, 32));
		}
	}

	if (t_movementDirection == Direction::Right)
	{
		if (m_animationCounter < 8)
		{
			t_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
		}
		else if (m_animationCounter < 16)
		{
			t_sprite.setTextureRect(sf::IntRect(64, 32, 32, 32));
		}
		else if (m_animationCounter < 24)
		{
			t_sprite.setTextureRect(sf::IntRect(64, 64, 32, 32));
		}
		else if (m_animationCounter < 32)
		{
			t_sprite.setTextureRect(sf::IntRect(64, 96, 32, 32));
		}
	}

	if (t_movementDirection == Direction::Left)
	{
		if (m_animationCounter < 8)
		{
			t_sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
		}
		else if (m_animationCounter < 16)
		{
			t_sprite.setTextureRect(sf::IntRect(96, 32, 32, 32));
		}
		else if (m_animationCounter < 24)
		{
			t_sprite.setTextureRect(sf::IntRect(96, 64, 32, 32));
		}
		else if (m_animationCounter < 32)
		{
			t_sprite.setTextureRect(sf::IntRect(96, 96, 32, 32));
		}
	}

	if (m_animationCounter >= 32) // reset counter
	{
		m_animationCounter = 0;
	}
}

/// <summary>
/// updates arrow
/// contains movement and hitbox detection calls
/// </summary>
void Game::updateArrow()
{
	m_arrow.travel();
	arrowHitDetection(m_arrow.getPosition()); // checks for collision with enemy
}

/// <summary>
/// updates javelins
/// </summary>
/// <param name="t_javelin"></param>
void Game::updateJavelin(Javelin& t_javelin)
{
	bool hitPlayer = false;

	hitPlayer = javelinHitDetecion(t_javelin.getPosition());

	if (hitPlayer == true)
	{
		t_javelin.setTraveling(false);
	}
}

/// <summary>
/// checks if stabber intersects with player
/// </summary>
/// <param name="t_stabberSprite"> sprite of stabber </param>
/// <returns> true if intersects, false if it doesn't intersect </returns>
bool Game::stabberhitDetection(sf::Sprite& t_stabberSprite)
{
	bool intersects = false;
	sf::FloatRect koboldHitbox = t_stabberSprite.getGlobalBounds();
	sf::FloatRect playerHitbox = m_player.getSprite().getGlobalBounds();

	// adjusted hit boxes
	float hitBoxWidth = 32.0f;
	float hitBoxHeight = 64.0f;

	adjustHitbox(koboldHitbox, hitBoxWidth, hitBoxHeight);
	adjustHitbox(playerHitbox, hitBoxWidth, hitBoxHeight);

	if (koboldHitbox.intersects(playerHitbox))
	{
		intersects = true;
	}

	return intersects;
}

/// <summary>
/// checks for projectile collision with enemies
/// </summary>
/// <param name="t_position"> position of projectile </param>
/// <returns> true if it intersects, false if no intersection</returns>
bool Game::arrowHitDetection(sf::Vector2f t_position)
{
	bool hit = false;
	sf::FloatRect koboldHitbox;
	float hitBoxWidth = 48.0f;
	float hitBoxHeight = 88.0f;

	for (short index = 0; index < NUMBER_STABBERS; index++)
	{
		if (m_stabberKobold[index].getStatus() != Status::dead) // only hit kobolds that are alive
		{
			koboldHitbox = m_stabberKobold[index].getSprite().getGlobalBounds();

			// hitbox modifications
			adjustHitbox(koboldHitbox, hitBoxWidth, hitBoxHeight);
		
			if (koboldHitbox.contains(t_position))
			{
				hit = true;
				m_arrow.setTraveling(false);
				m_stabberKobold[index].die();
			}
		}

		if (index >= NUMBER_THROWERS)
		{
			continue;
		}
		else
		{
			if (m_throwerKobold[index].getStatus() != Status::dead) // only hits kobolds that are alive
			{
				koboldHitbox = m_throwerKobold[index].getSprite().getGlobalBounds();

				// hitbox modifications
				adjustHitbox(koboldHitbox, hitBoxWidth, hitBoxHeight);;

				if (koboldHitbox.contains(t_position))
				{
					hit = true;
					m_arrow.setTraveling(false);
					m_throwerKobold[index].die();
				}
			}
		}
	}
	
	return hit;
}

/// <summary>
/// checks if Javelins hits Player
/// </summary>
/// <param name="t_position"> position of Javelin </param>
/// <returns> true if hit, false if no hit </returns>
bool Game::javelinHitDetecion(sf::Vector2f t_position)
{
	bool hitPlayer = false;
	sf::FloatRect playerHitbox = m_player.getSprite().getGlobalBounds();

	playerHitbox.left += 24.0f;
	playerHitbox.width = 48.0f;

	if (playerHitbox.contains(t_position) == true)
	{
		hitPlayer = true;
		m_player.takeDamage(m_throwerKobold->DAMAGE);
	}

	return hitPlayer;
}

/// <summary>
/// spawns new generic wave using randomized spawns 
/// </summary>
void Game::spawnGenericWave()
{
	float eastOrWest = static_cast<float>(rand() % 2);
	float spawnY = static_cast<float>(rand() % WINDOW_HEIGHT - 96.0f);
	sf::Vector2f spawnPoint;

	if (eastOrWest == 0.0f)
	{
		eastOrWest = -96.0f;
	}
	else
	{
		eastOrWest = WINDOW_WIDTH;
	}

	spawnPoint = { eastOrWest, spawnY };
}

/// <summary>
/// spawns first wave
/// </summary>
/// <returns></returns>
void Game::spawnWave1()
{
	sf::Vector2f stabberSpawn1{ -100.0f, 20.0f };
	sf::Vector2f stabberSpawn2{ WINDOW_WIDTH - 10.0f, 150.0f };
	sf::Vector2f throwerSpawn{ WINDOW_WIDTH - 10.0f, 100.0f };

	m_player.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 1.5F);

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