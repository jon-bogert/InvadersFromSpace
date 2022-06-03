#include "Pch.h"
#include "Application.h"

Application::Application()
	:
	clock(new sf::Clock())
{
	window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title);
	game = new Game(this);
}

Application::~Application()
{
	//Members
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

void Application::GameLoop()
{
	game->Start();
	while (window->isOpen())
	{
		sf::Event* windowEvent = new sf::Event;
		while (window->pollEvent(*windowEvent))
		{
			if (windowEvent->type == sf::Event::Closed)
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
