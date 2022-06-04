#pragma once

#include "Application.h"

class Application;


class MainMenu
{
	//Refs
	Application* app;
	sf::RenderWindow* window;

	//Properties
	bool exitMenu{};
	sf::Color selectedColor = {222, 83, 44, 255};
	sf::Color deselectedColor = {180, 180, 180, 255};
	int menuSelection = 0;
	bool showInstr{};

	//Text
	sf::Text* highScoreText;
	sf::Text* playText;
	sf::Text* instrText;
	sf::Text* quitText;

	//Sprites
	sf::Texture* bgTexture;
	sf::Sprite* bgSprite;
	sf::Texture* logoTexture;
	sf::Sprite* logoSprite;
	sf::Texture* controls1Texture;
	sf::Sprite* controls1Sprite;
	sf::Texture* controls2Texture;
	sf::Sprite* controls2Sprite;
	sf::Texture* instrTexture;
	sf::Sprite* instrSprite;
	sf::Texture* playerTexture;
	sf::Sprite* playerSprite;
	sf::Rect<int> playerSpriteFrame = { 0, 0, 99, 75 };


public:
	MainMenu(Application* app);
	~MainMenu();

	void Runtime();
	void Update();
	void Draw();

	void InstrUpdate();
	void InstrDraw();

private:
	void UpdateButtons();
	void ShipChange();
};

