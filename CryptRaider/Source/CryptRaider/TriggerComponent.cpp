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
	
	for (AActor* actor : actors)
	{
		if (actor->ActorHasTag(AcceptableActorTag))
		{
			UE_LOG(LogTemp, Display, TEXT("Unlocking"))
		}
	}
}
