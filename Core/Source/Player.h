#pragma once
#include "Application.h"
#include "Game.h"

class Application;
class Game;
class Enemy;

class Player
{
	//Refs
	Application* app;
	sf::RenderWindow* window;
	Game* game;

	//Members
	sf::Vector2<float> position;
	float scale = 0.5f;
	int lives = 3;
	int score = 0;
	std::vector<sf::Sprite*> lasers{};

	//Sprites
	sf::Texture* texture;
	sf::Sprite* sprite = nullptr;
	sf::Vector2<int> ss_res = { 99, 75 };
	sf::IntRect frame = {0, 0, ss_res.x, ss_res.y};
	int ss_numColors = 4;
	int ss_numTypes = 3;
	int ss_current = 0;

	sf::Texture* laserTexture;
	sf::Vector2<int> laserDim = { 9, 37 };

public:
	Player(Application* app);
	~Player();

	void SetupSprite();

	void Move();
	void Fire();
	void Draw();
	bool CheckCollision(Enemy* enemy);

	void ShipChange();

	int GetLives() const;
	void ReduceLives(const int amt = 1);
	void AddToScore(const int amt);

	sf::Sprite* GetSprite();
};

