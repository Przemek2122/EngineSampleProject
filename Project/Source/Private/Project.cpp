// Project.cpp : Defines the entry point for the application.

#include "Project.h"
#include "SDL3/SDL.h" // Include for SDL_Main
#include "Core/CoreEngine.h"
#include "ProjectEngine.h"

/**
 * Do not change main name,
 * SDL will replace this function and will run their own
 * to be able to use this code in multi-platform setup
 */
int main(int argc, char* argv[])
{
	FEngineManager EngineManager;
	EngineManager.Start<FDefaultEngine>(argc, argv);

	return 0;
}
