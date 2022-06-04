#pragma once
#include "Pch.h"

#include "Game.h"
#include "MainMenu.h"

class Game;
class MainMenu;

class Application
{
private:
	//Constants
	const sf::Vector2<int> REF_RESOLUTION = sf::Vector2<int>(405, 720);

	//References

	//Members
	sf::RenderWindow* window;
	Game* game;
	MainMenu* mm = nullptr;
	sf::Vector2<int> resolution = sf::Vector2<int>(405, 720);
	std::string title = "Invders From Space";
	sf::Color backgroundColor = sf::Color::Black;

	sf::Font* font;

	sf::Clock* clock;
	float deltaTime{};

	int highScore = 0;
	int playerType = 0;
	int playerColor = 0;

public:
	Application();
	~Application();
	Application(Application()) = delete;
	Application operator=(Application()) = delete;

	sf::RenderWindow* GetWindow();
	Game* GetGame();
	sf::Font* GetFont();

	void Runtime();

	sf::Vector2<int> GetResolution() const;
	sf::Vector2<float> GetResolutionScale() const;
	float DeltaTime() const;

	int GetHighScore() const;
	void SetHighScore(const int newHS);

	int GetPlayerType() const;
	int GetPlayerColor() const;
	void SetPlayerType(const int type);
	void SetPlayerColor(const int color);

private:
	void ResetGame();
	void Load();
	void Save();
};

