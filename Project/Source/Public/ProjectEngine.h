// Created by Przemys³aw Wiewióra 2020-2024 https://github.com/Przemek2122/Engine
#pragma once

#include "Core/CoreMinimal.h"
#include "Core/Engine.h"
#include "Core/Memory/AutoDeletePointer.h"

class FGameMode;
class FTextWidget;

class FDefaultEngine : public FEngine
{
public:
	FDefaultEngine();

	void Init() override;
	void Tick() override;
	void PostSecondTick() override;

protected:
	FWindow* GameWindow;
	FTextWidget* TextFPSWidget;
	FAutoDeletePointer<FGameMode> GameModePtr;
};
