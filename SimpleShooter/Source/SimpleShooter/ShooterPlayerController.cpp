// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* winScreen = CreateWidget(this, WinScreenClass);
		if (winScreen != nullptr)
		{
			winScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* loseScreen = CreateWidget(this, LoseScreenClass);
		if (loseScreen != nullptr)
		{
			loseScreen->AddToViewport();
		}
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
