#pragma once
namespace InputSystem
{
	//Player Movement
	bool MoveLeft();
	bool MoveRight();
	bool MoveUp();
	bool MoveDown();
	bool Fire();

	bool ChangeType();
	bool ChangeColor();

	bool MenuUp();
	bool MenuDown();
	bool MenuSelect();

	float DeadZone(const float input);
	sf::Vector2<float> MoveAxis();
	void MoveButtonAxis(sf::Vector2<float>& axis);
}

