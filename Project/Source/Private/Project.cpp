// Project.cpp : Defines the entry point for the application.
//

#include "Project.h"
#include "SDL3/SDL.h"
#include "Core/CoreEngine.h"

using namespace std;

int main(int argc, char* argv[])
{
	FEngineManager EngineManager;
	EngineManager.Start<FEngine>(argc, argv);

	return 0;
}
