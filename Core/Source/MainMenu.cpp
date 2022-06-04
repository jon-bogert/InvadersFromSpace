#include "Pch.h"
#include "MainMenu.h"
#include "InputSystem.h"

MainMenu::MainMenu(Application* app)
	: app(app),
	window(app->GetWindow())
{
	bgTexture = new sf::Texture;
	bgTexture->loadFromFile("Assets/stars-mm.png");
	bgSprite = new sf::Sprite;
	bgSprite->setTexture(*bgTexture);
	bgSprite->setTextureRect(sf::IntRect(0, 0, bgTexture->getSize().x, bgTexture->getSize().y));

	logoTexture = new sf::Texture;
	logoTexture->loadFromFile("Assets/logo.png");
	logoSprite = new sf::Sprite;
	logoSprite->setTexture(*logoTexture);
	logoSprite->setTextureRect(sf::IntRect(0, 0, logoTexture->getSize().x, logoTexture->getSize().y));
	logoSprite->setOrigin(logoSprite->getLocalBounds().width / 2, 0);
	logoSprite->setPosition(app->GetResolution().x / 2, 25);

	instrTexture = new sf::Texture;
	instrTexture->loadFromFile("Assets/instr.png");
	instrSprite = new sf::Sprite;
	instrSprite->setTexture(*instrTexture);
	instrSprite->setTextureRect(sf::IntRect(0, 0, instrTexture->getSize().x, instrTexture->getSize().y));

	controls1Texture = new sf::Texture;
	controls1Texture->loadFromFile("Assets/mm-controls-0.png");
	controls1Sprite = new sf::Sprite;
	controls1Sprite->setTexture(*controls1Texture);
	controls1Sprite->setTextureRect(sf::IntRect(0, 0, controls1Texture->getSize().x, controls1Texture->getSize().y));
	controls1Sprite->setOrigin(controls1Sprite->getLocalBounds().width / 2, 0);
	controls1Sprite->setPosition(app->GetResolution().x / 2, 500);

	controls2Texture = new sf::Texture;
	controls2Texture->loadFromFile("Assets/mm-controls-1.png");
	controls2Sprite = new sf::Sprite;
	controls2Sprite->setTexture(*controls2Texture);
	controls2Sprite->setTextureRect(sf::IntRect(0, 0, controls2Texture->getSize().x, controls2Texture->getSize().y));
	controls2Sprite->setOrigin(controls2Sprite->getLocalBounds().width / 2, 0);
	controls2Sprite->setPosition(150, 625);

	playerTexture = new sf::Texture;
	playerTexture->loadFromFile("Assets/player.png");
	playerSprite = new sf::Sprite;
	playerSprite->setTexture(*playerTexture);
	playerSpriteFrame.left = app->GetPlayerColor() * playerSpriteFrame.width;
	playerSpriteFrame.top = app->GetPlayerType() * playerSpriteFrame.height;
	playerSprite->setTextureRect(playerSpriteFrame);
	playerSprite->setScale(0.5f, 0.5f);
	playerSprite->setPosition(275, 635);

	//Text
	highScoreText = new sf::Text;
	highScoreText->setFont(*app->GetFont());
	highScoreText->setCharacterSize(20);
	highScoreText->setString("High Score: " + std::to_string(app->GetHighScore()));
	highScoreText->setOrigin(highScoreText->getLocalBounds().width / 2, 0);
	highScoreText->setPosition(app->GetResolution().x / 2, 250);

	playText = new sf::Text;
	playText->setFont(*app->GetFont());
	playText->setCharacterSize(30);
	playText->setString("Play Game");
	playText->setOrigin(playText->getLocalBounds().width / 2, 0);
	playText->setPosition(app->GetResolution().x / 2, 325);
	playText->setFillColor(selectedColor);

	instrText = new sf::Text;
	instrText->setFont(*app->GetFont());
	instrText->setCharacterSize(30);
	instrText->setString("Instructions");
	instrText->setOrigin(instrText->getLocalBounds().width / 2, 0);
	instrText->setPosition(app->GetResolution().x / 2, 375);
	instrText->setFillColor(deselectedColor);

	quitText = new sf::Text;
	quitText->setFont(*app->GetFont());
	quitText->setCharacterSize(30);
	quitText->setString("Quit Game");
	quitText->setOrigin(quitText->getLocalBounds().width / 2, 0);
	quitText->setPosition(app->GetResolution().x / 2, 425);
	quitText->setFillColor(deselectedColor);

}

MainMenu::~MainMenu()
{
	delete bgSprite;
	delete bgTexture;
	delete logoSprite;
	delete logoTexture;
	delete controls1Sprite;
	delete controls1Texture;
	delete controls2Sprite;
	delete controls2Texture;
	delete instrTexture;
	delete instrSprite;
	delete playerTexture;
	delete playerSprite;

	delete highScoreText;
	delete playText;
	delete instrText;
	delete quitText;
}

void MainMenu::Runtime()
{
	while (window->isOpen() && !exitMenu)
	{
		sf::Event* windowEvent = new sf::Event;
		while (window->pollEvent(*windowEvent))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window->close();
			}
		}
		delete windowEvent;

		(showInstr) ? InstrUpdate() : Update();

		window->clear(sf::Color::Black);
		(showInstr) ? InstrDraw() : Draw();
		window->display();
	}
}

void MainMenu::Update()
{
	if (InputSystem::MenuDown())
	{
		menuSelection = (menuSelection + 1) % 3;
		UpdateButtons();
	}
	if (InputSystem::MenuUp())
	{
		menuSelection = (menuSelection == 0) ? 2 : menuSelection - 1;
		UpdateButtons();
	}
	if (InputSystem::MenuSelect())
	{
		switch (menuSelection)
		{
		case 0:
			exitMenu = true;
			break;
		case 1:
			showInstr = true;
			break;
		case 2:
			window->close();
			break;
		}
	}
	ShipChange();
}

void MainMenu::Draw()
{
	window->draw(*bgSprite);
	window->draw(*logoSprite);
	window->draw(*highScoreText);
	window->draw(*playText);
	window->draw(*instrText);
	window->draw(*quitText);
	window->draw(*controls1Sprite);
	window->draw(*controls2Sprite);
	window->draw(*playerSprite);
}

void MainMenu::InstrUpdate()
{
	if (InputSystem::MenuSelect()) showInstr = false;
}

void MainMenu::InstrDraw()
{
	window->draw(*bgSprite);
	window->draw(*instrSprite);
}

void MainMenu::UpdateButtons()
{
	switch (menuSelection)
	{
	case 0:
		playText->setFillColor(selectedColor);
		instrText->setFillColor(deselectedColor);
		quitText->setFillColor(deselectedColor);
		break;
	case 1:
		playText->setFillColor(deselectedColor);
		instrText->setFillColor(selectedColor);
		quitText->setFillColor(deselectedColor);
		break;
	case 2:
		playText->setFillColor(deselectedColor);
		instrText->setFillColor(deselectedColor);
		quitText->setFillColor(selectedColor);
		break;

	}
}

void MainMenu::ShipChange()
{

	if (InputSystem::ChangeType())
	{
		app->SetPlayerType((app->GetPlayerType() + 1) % 3);
		playerSpriteFrame.top = app->GetPlayerType() * playerSpriteFrame.height;
		playerSprite->setTextureRect(playerSpriteFrame);
	}
	if (InputSystem::ChangeColor())
	{
		app->SetPlayerColor((app->GetPlayerColor() + 1) % 4);
		playerSpriteFrame.left = app->GetPlayerColor() * playerSpriteFrame.width;
		playerSprite->setTextureRect(playerSpriteFrame);
	}
}
