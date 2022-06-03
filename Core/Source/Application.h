#pragma once
#include "Pch.h"

#include "Game.h"

class Game;

class Application
{
private:
	//Constants
	const sf::Vector2<int> REF_RESOLUTION = sf::Vector2<int>(405, 720);

	//References

	//Members
	sf::RenderWindow* window;
	Game* game;
	sf::Vector2<int> resolution = sf::Vector2<int>(405, 720);
	std::string title = "Invders From Space";
	sf::Color backgroundColor = sf::Color::Black;

	sf::Clock* clock;
	float deltaTime{};

public:
	Application();
	~Application();
	Application(Application()) = delete;
	Application operator=(Application()) = delete;

	sf::RenderWindow* GetWindow();
	Game* GetGame();

	void GameLoop();

	sf::Vector2<int> GetResolution() const;
	sf::Vector2<float> GetResolutionScale() const;
	float DeltaTime() const;
};

