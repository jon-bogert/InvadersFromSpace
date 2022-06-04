#include "Pch.h"
#include "Application.h"

Application::Application()
	:
	clock(new sf::Clock())
{
	window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title, sf::Style::None);
	game = new Game(this);
	font = new sf::Font;
	font->loadFromFile("Assets/archia-semibold.ttf");
}

Application::~Application()
{
	//Members
	delete font;
	delete clock;
	delete window;
}

sf::RenderWindow* Application::GetWindow()
{
	return window;
}

Game* Application::GetGame()
{
	return game;
}

sf::Font* Application::GetFont()
{
	return font;
}

void Application::Runtime()
{
	Load();
	while (window->isOpen())
	{
		mm = new MainMenu(this);
		mm->Runtime();
		delete mm; mm = nullptr;

		game->Start();
		clock->restart();
		while (!game->GetGameOver() && window->isOpen())
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

			deltaTime = clock->getElapsedTime().asSeconds();
			clock->restart();

			game->Update();

			window->clear(backgroundColor);
			game->Draw();
			window->display();
		}
		ResetGame();
	}
	Save();
}

sf::Vector2<int> Application::GetResolution() const
{
	return resolution;
}

sf::Vector2<float> Application::GetResolutionScale() const
{
	return sf::Vector2<float>
		(
		(float)resolution.x / (float) REF_RESOLUTION.x,
		(float)resolution.y / (float)REF_RESOLUTION.y
		);
}

float Application::DeltaTime() const
{
	return deltaTime;
}

int Application::GetHighScore() const
{
	return highScore;
}

void Application::SetHighScore(const int newHS)
{
	highScore = newHS;
}

int Application::GetPlayerType() const
{
	return playerType;
}

int Application::GetPlayerColor() const
{
	return playerColor;
}

void Application::SetPlayerType(const int type)
{
	playerType = type;
}

void Application::SetPlayerColor(const int color)
{
	playerColor = color;
}

void Application::ResetGame()
{
	delete game;
	game = new Game(this);
}

void Application::Load()
{
	std::ifstream file("pls_dont_edit_lol.sav");
	if (!file.is_open())
	{
		Save(); // create new file
		return;
	}
	std::string data;

	std::getline(file, data);

	highScore = atoi(data.c_str());

	file.close();
}

void Application::Save()
{
	srand(time(NULL));
	std::ofstream file("pls_dont_edit_lol.sav");
	file << std::to_string(highScore);
	file.close();
}
