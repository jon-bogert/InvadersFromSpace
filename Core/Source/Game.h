#pragma once
#include "Application.h"
#include "Player.h"

class Application;
class Player;

class Game
{
	//References
	Application* app;
	sf::RenderWindow* window;

	//Members
	std::map<std::string, sf::Texture*> textures; // Store game textures here
	sf::Sprite* background = nullptr;

	Player* player;


public:
	Game(Application* app);
	~Game();

	void Start();
	void Update();
	void Draw();

	void InitTextures();

	sf::Texture* GetTexture(std::string key);


private:
	void AddTexture(std::string key, std::string path);
	
};

