#include "Pch.h"
#include "Enemy.h"

const float MOVE_SPEED = 25.f;
const int DOWN_AMT = 20;

Enemy::Enemy(Application* app, int type, sf::Vector2<float> startPos, sf::Texture* texture)
	:app(app),
	window(app->GetWindow()),
	game(app->GetGame()),
	position(startPos)
{
	if (type > 2)
	{
		std::cout << "ERROR: Enemy type must be 0, 1, or 2" << std::endl;
		abort();
	}

	sprite = new sf::Sprite;
	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(type * ss_res.x, 0, ss_res.x, ss_res.y));
	sprite->setScale(scale, scale);

	switch (type)
	{
	case 0:
		points = 10;
		break;
	case 1:
		points = 20;
		break;
	default:
		points = 30;
	}
}

Enemy::~Enemy()
{
	delete sprite;
}

void Enemy::Draw()
{
	sprite->setPosition(position);
	window->draw(*sprite);
}

sf::Sprite* Enemy::GetSprite()
{
	return sprite;
}

int Enemy::GetPoints() const
{
	return points;
}

sf::Vector2<float> Enemy::GetPosition() const
{
	return position;
}

void Enemy::Move(bool isGoingLeft, bool goDown)
{
	if (goDown)
	{
		position.y += DOWN_AMT;
	}

	if (isGoingLeft)
	{
		position.x -= MOVE_SPEED * app->DeltaTime();
	}
	else
	{
		position.x += MOVE_SPEED * app->DeltaTime();
	}
}
