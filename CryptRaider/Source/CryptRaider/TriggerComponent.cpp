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

	AActor* actor = GetAcceptableActor();
	if (actor != nullptr)
	{
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(actor->GetRootComponent());
		if (component != nullptr)
		{
			component->SetSimulatePhysics(false);
			component->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Mover->SetShouldMove(true);
		}
	}
	else
	{
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* mover)
{
	Mover = mover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors);

	for (AActor* actor : actors)
	{
		bool hasAcceptableTag = actor->ActorHasTag(AcceptableActorTag);
		bool isGrabbed = actor->ActorHasTag("Grabbed");
		if (hasAcceptableTag && !isGrabbed)
		{
			return actor;
		}
	}

	return nullptr;
}
