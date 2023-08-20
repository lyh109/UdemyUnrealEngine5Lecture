// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> actors;
	GetOverlappingActors(actors);
	
	/*int32 index = 0;
	while (index < actors.Num())
	{
		UE_LOG(LogTemp, Display, TEXT("Overlapping actor: %s"), *actors[index]->GetActorNameOrLabel());
		++index;
	}*/

	for (int32 i = 0; i < actors.Num(); ++i)
	{
		UE_LOG(LogTemp, Display, TEXT("Overlapping actor: %s"), *actors[i]->GetActorNameOrLabel());
	}
}
