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

void Application::GameLoop()
{
	Load();
	//Save();
	while (window->isOpen())
	{
		game->Start();
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

void Application::ResetGame()
{
	delete game;
	game = new Game(this);
}

void Application::Load()
{
	std::ifstream file("data.sav");
	std::string data;
	std::string score;

	for (int i = 0; i < 17; i++)
	{
		std::getline(file, data);
	}
	for (char c : data)
	{
		score.push_back(c - 48);
	}
	std::cout << score << std::endl;


	file.close();
}

void Application::Save()
{
	srand(time(NULL));
	std::ofstream file("data.sav");
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < rand() % 500; j++)
		{
			file << (char)((rand() % 233) + 23);
		}
		file << std::endl;
	}
	std::string score = std::to_string(highScore);
	for (char c : score)
	{
		file << (char)( c + 48);
	}
	file << std::endl;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < rand() % 500; j++)
		{
			file << (char)((rand() % 233) + 23);
		}
		file << std::endl;
	}
	file.close();
}
