#include "ProjectEngine.h"
#include "ProjectGameMode.h"
#include "Engine/Logic/GameModeManager.h"
#include "Renderer/Widgets/Samples/ButtonWidget.h"
#include "Renderer/Widgets/Samples/MouseSparkWidget.h"
#include "Renderer/Widgets/Samples/TextWidget.h"
#include "Renderer/Widgets/Samples/VerticalBoxWidget.h"

FProjectEngine::FProjectEngine()
	: GameWindow(nullptr)
	, TextFPSWidget(nullptr)
	, GameModeManager(nullptr)
	, GameMode(nullptr)
{
}

void FProjectEngine::Init()
{
	FEngine::Init();

	LOG_DEBUG("Game init");

	FWindowCreationData WindowCreationData(false);
	const FVector2D<int32> NewWindowLocation = { 200, 200 };
	const FVector2D<int32> NewWindowSize = { 800, 600 };
	GameWindow = GEngine->GetEngineRender()->CreateWindow<FWindow>(WindowCreationData, "Sample window", NewWindowLocation, NewWindowSize);
	if (GameWindow != nullptr)
	{
		// Create game mode subsystem for window
		GameModeManager = GameWindow->CreateSubSystem<FGameModeManager>(GameWindow);
		GameMode = GameModeManager->CreateGameMode<FProjectGameMode>(true);

		// Add sample 'FMouseSparkWidget' widget
		FWidgetManager* GameWindowWidgetManager = GameWindow->GetWidgetManager();

		GameWindowWidgetManager->CreateWidget<FMouseSparkWidget>("TestSparkWidget", 100);
		TextFPSWidget = GameWindowWidgetManager->CreateWidget<FTextWidget>("TextFPS");
		TextFPSWidget->SetText("FPS");
		TextFPSWidget->SetAnchor(EAnchor::RightTop);

		FVerticalBoxWidget* VerticalBoxWidget = GameWindow->GetWidgetManager()->CreateWidget<FVerticalBoxWidget>("TestVerticalBoxWidget");
		VerticalBoxWidget->SetAnchor(EAnchor::Center);

		FButtonWidget* StartButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		FTextWidget* StartTextWidget = StartButtonWidget->CreateWidget<FTextWidget>();
		StartTextWidget->SetText("Start");
		StartButtonWidget->OnLeftClickPress.BindLambda([this, VerticalBoxWidget]
		{
			LOG_DEBUG("Start requested!");

			GameWindow->DestroyWidget(VerticalBoxWidget);

			//GameMode->StartGame();
		});

		FButtonWidget* ExitButtonWidget = VerticalBoxWidget->CreateWidget<FButtonWidget>();
		FTextWidget* ExitTextWidget = ExitButtonWidget->CreateWidget<FTextWidget>();
		ExitTextWidget->SetText("Exit");
		ExitButtonWidget->OnLeftClickPress.BindLambda([this]
		{
			LOG_DEBUG("Exit requested!");

			RequestExit();
		});
	}
}

void FProjectEngine::Tick()
{
	FEngine::Tick();
}

void FProjectEngine::PostSecondTick()
{
	FEngine::PostSecondTick();
}
