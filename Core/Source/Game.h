#pragma once
#include "Application.h"
#include "Player.h"
#include "Enemy.h"

class Application;
class Player;
class Enemy;

class Game
{
	//References
	Application* app;
	sf::RenderWindow* window;

	//Members
	sf::Texture* bgTexture; // Store game textures here
	sf::Texture* enemyTexture;
	sf::Sprite* background = nullptr;

	Player* player;
	std::vector<Enemy*> enemies{};
	bool enemyDown{};
	bool enemyLeft{};


public:
	Game(Application* app);
	~Game();

	void Start();
	void Update();
	void Draw();

	void InitTextures();

	sf::Texture* GetEnemyTexture();

private:
	void SetupEnemies();
};

