#include "Pch.h"
#include "InputSystem.h"

const float L_DEADZONE_MIN = 0.3f;
const float L_DEADZONE_MAX = 1.0f;

const float AXIS_THROW = 0.5f;

sf::Vector2<float> moveAxis{};

//Active Triggers
bool changeTypeTrig = false;
bool changeColorTrig = false;
bool fireTrig = true;
bool menuSelectTrig = false;
bool menuDownTrig = false;
bool menuUpTrig = false;


bool InputSystem::MoveLeft()
{
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
}

bool InputSystem::MoveRight()
{
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
}

bool InputSystem::MoveUp()
{
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
}

bool InputSystem::MoveDown()
{
    return (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
}

bool InputSystem::Fire()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Joystick::isButtonPressed(0, 0))
	{
		if (!fireTrig)
		{
			fireTrig = true;
			return true;
		}
	}
	else if (fireTrig)
		fireTrig = false;
	return false;
}

bool InputSystem::ChangeType()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) ||
		sf::Joystick::isButtonPressed(0, 2))
	{
		if (!changeTypeTrig)
		{
			changeTypeTrig = true;
			return true;
		}
	}
	else if (changeTypeTrig)
		changeTypeTrig = false;
	return false;
}

bool InputSystem::ChangeColor()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) ||
		sf::Joystick::isButtonPressed(0, 3))
	{
		if (!changeColorTrig)
		{
			changeColorTrig = true;
			return true;
		}
	}
	else if (changeColorTrig)
		changeColorTrig = false;
	return false;
}

bool InputSystem::MenuUp()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		MoveAxis().y < 0)
	{
		if (!menuUpTrig)
		{
			menuUpTrig = true;
			return true;
		}
	}
	else if (menuUpTrig)
		menuUpTrig = false;
	return false;
}

bool InputSystem::MenuDown()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		MoveAxis().y > 0)
	{
		if (!menuDownTrig)
		{
			menuDownTrig = true;
			return true;
		}
	}
	else if (menuDownTrig)
		menuDownTrig = false;
	return false;
}

bool InputSystem::MenuSelect()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Joystick::isButtonPressed(0, 0))
	{
		if (!menuSelectTrig)
		{
			menuSelectTrig = true;
			return true;
		}
	}
	else if (menuSelectTrig)
		menuSelectTrig = false;
	return false;
}

float InputSystem::DeadZone(const float input)
{
	if (fabs(input) < L_DEADZONE_MIN)
	{
		return 0.f;
	}
	else if (fabs(input) > L_DEADZONE_MAX)
	{
		if (input >= 0.f) { return 1.f; }
		else { return -1.f; }
	}
	else
	{
		if (input >= 0.f)
		{
			return (input - L_DEADZONE_MIN) * (1 / (L_DEADZONE_MAX - L_DEADZONE_MIN));
		}
		else
		{
			return (input + L_DEADZONE_MIN) * (1 / (L_DEADZONE_MAX - L_DEADZONE_MIN));
		}
	}
}

sf::Vector2<float> InputSystem::MoveAxis()
{
	sf::Vector2<float> tempAxis;
	if (sf::Joystick::isConnected(0))
	{
		tempAxis.x = DeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100.f);
		tempAxis.y = DeadZone(sf::Joystick::getAxisPosition(0, sf::Joystick::Y)/ 100.f);
		if ((tempAxis.x == 0.f) && (tempAxis.y == 0.f))
		{
			MoveButtonAxis(moveAxis);
		}
		else
		{
			moveAxis = tempAxis;
		}
	}
	else
	{
		MoveButtonAxis(moveAxis);
	}
	return moveAxis;
}

void InputSystem::MoveButtonAxis(sf::Vector2<float>& axis)
{
	sf::Vector2<float> targetValue = { 0.f, 0.f };
	if (MoveRight())
	{
		targetValue.x = 1.f;
	}
	if (MoveLeft())
	{
		targetValue.x = -1.f;
	}
	if (MoveDown())
	{
		targetValue.y = 1.f;
	}
	if (MoveUp())
	{
		targetValue.y = -1.f;
	}

	if ((targetValue.x != 0.f) && (targetValue.y != 0.f))
	{
		targetValue.x = sqrtf(0.5f) * targetValue.x;
		targetValue.y = sqrtf(0.5f) * targetValue.y;
	}

	if ((axis.x < targetValue.x) && (axis.x + AXIS_THROW < targetValue.x))
	{
		axis.x += AXIS_THROW;
	}
	else if ((axis.x > targetValue.x) && (axis.x - AXIS_THROW > targetValue.x))
	{
		axis.x -= AXIS_THROW;
	}
	else if (((axis.x < targetValue.x) && (axis.x + AXIS_THROW >= targetValue.x))
		|| ((axis.x > targetValue.x) && (axis.x - AXIS_THROW <= targetValue.x)))
	{
		axis.x = targetValue.x;
	}

	if ((axis.y < targetValue.y) && (axis.y + AXIS_THROW < targetValue.y))
	{
		axis.y += AXIS_THROW;
	}
	else if ((axis.y > targetValue.y) && (axis.y - AXIS_THROW > targetValue.y))
	{
		axis.y -= AXIS_THROW;
	}
	else if (((axis.y < targetValue.y) && (axis.y + AXIS_THROW >= targetValue.y))
		|| ((axis.y > targetValue.y) && (axis.y - AXIS_THROW <= targetValue.y)))
	{
		axis.y = targetValue.y;
	}
}
