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
	delete background;
	for (auto texture : textures)
	{
		delete texture.second;
	}
}

void Game::Start()
{
	window->setFramerateLimit(60);
	InitTextures();
	background = new sf::Sprite();
	background->setTexture(*GetTexture("bg"));
	background->setTextureRect(sf::Rect(0, 0, (int)GetTexture("bg")->getSize().x, (int)GetTexture("bg")->getSize().y));
	background->setPosition(0, 0);
	
	player->SetupSprite();
}

void Game::Update()
{
	player->ShipChange();
	player->Move();
	player->Fire();
}

void Game::Draw()
{
	window->draw(*background);
	player->Draw();
}

void Game::InitTextures()
{
	AddTexture("bg", "Assets/stars.png");
	AddTexture("player", "Assets/player.png");
}



void Game::AddTexture(std::string key, std::string path)
{
	textures.emplace(std::make_pair(key, new sf::Texture));
	if (!textures[key]->loadFromFile(path))
	{
		std::cout << "Could not load '" << key << "' from " << path << std::endl;
		delete textures[key];
		textures.erase(key);
	}
}

sf::Texture* Game::GetTexture(std::string key)
{
	return textures[key];
}
