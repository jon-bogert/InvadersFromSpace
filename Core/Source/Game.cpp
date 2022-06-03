#include "Pch.h"
#include "Game.h"
#include "InputSystem.h"

Game::Game(Application* app)
	:
	app(app),
	window(app->GetWindow()),
	player(new Player(app))
{
}

Game::~Game()
{
	delete player;
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	delete background;
	delete bgTexture;
	delete enemyTexture;
}

void Game::Start()
{
	window->setFramerateLimit(165);
	InitTextures();
	background = new sf::Sprite();
	background->setTexture(*bgTexture);
	background->setTextureRect(sf::Rect(0, 0, (int)bgTexture->getSize().x, (int)bgTexture->getSize().y));
	background->setPosition(0, 0);

	player->SetupSprite();

	SetupEnemies();
}

void Game::Update()
{
	player->ShipChange();
	player->Move();
	player->Fire();

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
}

void Game::Draw()
{
	window->draw(*background);
	player->Draw();
	for (Enemy* enemy : enemies)
	{
		enemy->Draw();
	}
}

void Game::InitTextures()
{
	bgTexture = new sf::Texture;
	bgTexture->loadFromFile("Assets/stars.png");

	enemyTexture = new::sf::Texture;
	enemyTexture->loadFromFile("Assets/enemy.png");
}

sf::Texture* Game::GetEnemyTexture()
{
	return enemyTexture;
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
