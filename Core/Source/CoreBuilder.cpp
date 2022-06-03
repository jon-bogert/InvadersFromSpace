#include "Pch.h"
#include "Application.h"

int main()
{
	Application* application = new Application();

	application->GameLoop();

	delete application;

	return 0;
}