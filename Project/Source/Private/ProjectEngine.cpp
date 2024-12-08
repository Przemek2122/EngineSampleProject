#include "ProjectEngine.h"

FDefaultEngine::FDefaultEngine()
	: GameWindow(nullptr)
	, TextFPSWidget(nullptr)
{
}

void FDefaultEngine::PreInit()
{
	FEngine::PreInit();
}

void FDefaultEngine::Init()
{
	FEngine::Init();
}

void FDefaultEngine::PostInit()
{
	FEngine::PostInit();
}

void FDefaultEngine::Tick()
{
	FEngine::Tick();
}

void FDefaultEngine::PostSecondTick()
{
	FEngine::PostSecondTick();
}
