#include "Pch.h"
#include "Application.h"

int main()
{
	Application* application = new Application();

	application->Runtime();

	delete application;

	return 0;
}