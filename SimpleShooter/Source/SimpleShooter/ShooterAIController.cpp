// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), playerPawn->GetActorLocation());
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