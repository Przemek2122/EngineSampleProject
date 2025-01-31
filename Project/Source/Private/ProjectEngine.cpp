#include "ProjectEngine.h"

FDefaultEngine::FDefaultEngine()
	: GameWindow(nullptr)
	, TextFPSWidget(nullptr)
{
}

void FDefaultEngine::Init()
{
	FEngine::Init();

	// ...
}

void FDefaultEngine::Tick()
{
	FEngine::Tick();
}

void FDefaultEngine::PostSecondTick()
{
	FEngine::PostSecondTick();
}
