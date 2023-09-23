// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>INPUT_MAPPING_CONTEXT(TEXT("/Game/Input/IMC_Shooter.IMC_Shooter"));
	if (INPUT_MAPPING_CONTEXT.Succeeded())
	{
		InputMappingContext = INPUT_MAPPING_CONTEXT.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE_FORWARD(TEXT("/Game/Input/IA_MoveForward.IA_MoveForward"));
	if (IA_MOVE_FORWARD.Succeeded())
	{
		MoveForwardAction = IA_MOVE_FORWARD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK_UP(TEXT("/Game/Input/IA_LookUp.IA_LookUp"));
	if (IA_LOOK_UP.Succeeded())
	{
		LookUpAction = IA_LOOK_UP.Object;
	}
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			subSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	 if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	 {
		 EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveForward);
		 EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUp);
	 }
}

void AShooterCharacter::MoveForward(const FInputActionValue& value)
{
	const FVector2D movement = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector() * movement.Y);
}

void AShooterCharacter::LookUp(const FInputActionValue& value)
{
	const float movement = value.Get<float>();
	AddControllerPitchInput(movement);
}
