#include "Pch.h"
#include "Game.h"
#include "InputSystem.h"

const float ENEMY_LASER_SPEED = 500.f;

Game::Game(Application* app)
	:
	app(app),
	window(app->GetWindow()),
	player(new Player(app)),
	enemyShotClock(new sf::Clock)
{
}

Game::~Game()
{
	delete enemyShotClock;
	delete player;
	for (sf::Sprite* laser : enemyLasers)
		delete laser;
	delete enemyLaserTexture;
	for (Enemy* enemy : enemies)
		delete enemy;
	delete background;
	delete bgTexture;
	delete enemyTexture;
	delete scoreText;
}

void Game::Start()
{
	srand(time(NULL));
	window->setFramerateLimit(165);

	InitTextures();
	//Background
	background = new sf::Sprite();
	background->setTexture(*bgTexture);
	background->setTextureRect(sf::Rect(0, 0, (int)bgTexture->getSize().x, (int)bgTexture->getSize().y));
	background->setPosition(0, 0);

	//Text
	scoreText = new sf::Text;
	scoreText->setFont(*app->GetFont());
	scoreText->setCharacterSize(20);
	scoreText->setString("Score: XXXX");
	scoreText->setPosition(10, 10);

	livesText = new sf::Text;
	livesText->setFont(*app->GetFont());
	livesText->setCharacterSize(20);
	livesText->setString("Lives: X");
	livesText->setOrigin(livesText->getGlobalBounds().width, 0);
	livesText->setPosition(app->GetResolution().x - 10, 10);
	
	//GameObjects
	player->SetupSprite();

	SetupEnemies();
	enemyShotClock->restart();
}

void Game::Update()
{
	player->ShipChange();
	player->Move();
	player->Fire();

	EnemyDeath();
	MoveEnemies();
	EnemyFire();
	PlayerDeath();
}

void Game::EnemyFire()
{
	if (enemyShotClock->getElapsedTime().asSeconds() > enemyStotTime && enemies.size() != 0)
	{
		int enemyIndex = rand() % enemies.size();
		int i = enemyLasers.size();

		enemyLasers.push_back(new sf::Sprite);
		enemyLasers[i]->setTexture(*enemyLaserTexture);
		enemyLasers[i]->setTextureRect(sf::IntRect(0, 0, (int)enemyLaserTexture->getSize().x, (int)enemyLaserTexture->getSize().y));
		enemyLasers[i]->setScale(scale, scale);
		enemyLasers[i]->setPosition(enemies[enemyIndex]->GetPosition().x + (enemyLaserTexture->getSize().x / 2) * scale,
			enemies[enemyIndex]->GetPosition().y + enemies[enemyIndex]->GetSprite()->getGlobalBounds().height);

		enemyShotClock->restart();
	}

	//Check Expiry
	int i = 0;
	while (i < enemyLasers.size())
	{
		if (enemyLasers[i]->getPosition().y < -50)
		{
			delete enemyLasers[i];
			enemyLasers.erase(enemyLasers.begin() + i);
		}
		else
			i++;
	}
}

void Game::MoveEnemies()
{
	bool triggDown{};
	for (Enemy* enemy : enemies)
	{
		enemy->Move(enemyLeft, enemyDown);
		if (enemy->GetPosition().x > app->GetResolution().x - enemy->GetSprite()->getGlobalBounds().width && !enemyLeft)
		{
			enemyLeft = true;
			triggDown = true;
		}
		else if (enemy->GetPosition().x < 0 && enemyLeft)
		{
			enemyLeft = false;
			triggDown = true;
		}
	}
	enemyDown = triggDown;

	//Lasers
	for (sf::Sprite* laser : enemyLasers)
	{
		laser->setPosition(laser->getPosition().x, laser->getPosition().y + (ENEMY_LASER_SPEED * app->DeltaTime()));
	}
}

void Game::EnemyDeath()
{
	int i = 0;
	while (i < enemies.size())
	{
		if (player->CheckCollision(enemies[i]))
		{
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
		else i++;
	}
}

void Game::PlayerDeath()
{
	int i = 0;
	while (i < enemyLasers.size())
	{
		sf::Sprite* laser = enemyLasers[i];
		if (laser->getGlobalBounds().left < player->GetSprite()->getGlobalBounds().left + player->GetSprite()->getGlobalBounds().width &&
			laser->getGlobalBounds().left + laser->getGlobalBounds().width > player->GetSprite()->getGlobalBounds().left &&
			laser->getGlobalBounds().top < player->GetSprite()->getGlobalBounds().top + player->GetSprite()->getGlobalBounds().height &&
			laser->getGlobalBounds().top + laser->getGlobalBounds().height > player->GetSprite()->getGlobalBounds().top)
		{
			player->ReduceLives();
			delete enemyLasers[i];
			enemyLasers.erase(enemyLasers.begin() + i);
			return;
		}
		i++;
	}
}

void Game::Draw()
{
	window->draw(*background);
	player->Draw();
	for (sf::Sprite* laser : enemyLasers)
	{
		window->draw(*laser);
	}
	for (Enemy* enemy : enemies)
	{
		enemy->Draw();
	}
	window->draw(*scoreText);
	window->draw(*livesText);
}

void Game::InitTextures()
{
	bgTexture = new sf::Texture;
	bgTexture->loadFromFile("Assets/stars.png");

	enemyTexture = new::sf::Texture;
	enemyTexture->loadFromFile("Assets/enemy.png");

	enemyLaserTexture = new sf::Texture;
	enemyLaserTexture->loadFromFile("Assets/enemy-laser.png");
}

void Game::UpdateScoreText(int newScore)
{
	scoreText->setString("Score: " + std::to_string(newScore));
}

void Game::UpdateLivesText(int newLives)
{
	livesText->setString("Lives: " + std::to_string(newLives));
}

sf::Texture* Game::GetEnemyTexture()
{
	return enemyTexture;
}

void Game::GameOver()
{
	gameOver = true;
}

bool Game::GetGameOver() const
{
	return gameOver;
}

void Game::SetupEnemies()
{
	int posX{}, posY = 75;
	int spX = 52, spY = 50;

	//Type 2
	for (int i = 0; i < 7; i++)
	{
		enemies.push_back(new Enemy(app, 2, { (float)posX, (float)posY }, enemyTexture));
		posX += spX;
	}
	posX = 0;
	posY += spY;
	// Type 1
	for (int i = 0; i < 7; i++)
	{
		enemies.push_back(new Enemy(app, 1, { (float)posX, (float)posY }, enemyTexture));
		posX += spX;
	}
	posX = 0;
	posY += spY;
	for (int i = 0; i < 7; i++)
	{
		enemies.push_back(new Enemy(app, 1, { (float)posX, (float)posY }, enemyTexture));
		posX += spX;
	}
	//Type 0
	posX = 0;
	posY += spY;
	for (int i = 0; i < 7; i++)
	{
		enemies.push_back(new Enemy(app, 0, { (float)posX, (float)posY }, enemyTexture));
		posX += spX;
	}
	posX = 0;
	posY += spY;
	for (int i = 0; i < 7; i++)
	{
		enemies.push_back(new Enemy(app, 0, { (float)posX, (float)posY }, enemyTexture));
		posX += spX;
	}
}
