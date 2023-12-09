// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* playerController = Cast<APlayerController>(PawnKilled->GetController());
	if (playerController != nullptr)
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = controller->IsPlayerController() == bIsPlayerWinner;
		controller->GameHasEnded(controller->GetPawn(), bIsWinner);
	}
}
