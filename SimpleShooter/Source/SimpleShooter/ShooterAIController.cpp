// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	 if (LineOfSightTo(playerPawn))
	 {
	 	SetFocus(playerPawn);
	 	MoveToActor(playerPawn, AcceptanceRadius);
	 }
	 else
	 {
	 	ClearFocus(EAIFocusPriority::Gameplay);
	 	StopMovement();
	 }*/
}