#pragma once
#include "Application.h"
#include "Game.h"

class Application;
class Game;

class Enemy
{
	//Refs
	Application* app;
	sf::RenderWindow* window;
	Game* game;

	sf::Vector2<float> position;
	int points;

	//Textures
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite;
	sf::Vector2<int> ss_res = { 93, 84 };
	float scale = 0.5f;


public:
	Enemy(Application* app, int type, sf::Vector2<float> startPos, sf::Texture* texture);
	~Enemy();

	void Draw();
	sf::Sprite* GetSprite();

	int GetPoints() const;
	sf::Vector2<float> GetPosition() const;

	void Move(bool isGoingLeft, bool goDown);
};