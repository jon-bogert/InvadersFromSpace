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
	sf::Texture* bgTexture = nullptr;
	sf::Texture* enemyTexture = nullptr;
	sf::Texture* enemyLaserTexture = nullptr;
	sf::Sprite* background = nullptr;
	float scale = 0.5f;

	Player* player;
	std::vector<Enemy*> enemies{};
	bool enemyDown{};
	bool enemyLeft{};
	std::vector<sf::Sprite*> enemyLasers{};

	sf::Clock* enemyShotClock;
	float enemyStotTime = 1.f;


public:
	Game(Application* app);
	~Game();

	void Start();
	void Update();
	void EnemyFire();
	void MoveEnemies();
	void EnemyDeath();
	void PlayerDeath();
	void Draw();

	void InitTextures();

	sf::Texture* GetEnemyTexture();

private:
	void SetupEnemies();
};

