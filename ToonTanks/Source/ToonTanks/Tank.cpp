// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT(TEXT("/Game/Blueprints/Input/IMC_Tank.IMC_Tank"));
	if (DEFAULT_CONTEXT.Succeeded())
	{
		DefaultContext = DEFAULT_CONTEXT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE(TEXT("/Game/Blueprints/Input/IA_Movement.IA_Movement"));
	if (IA_MOVE.Succeeded())
	{
		MoveAction = IA_MOVE.Object;
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
			subSystem->AddMappingContext(DefaultContext, 0);
	}
}

void ATank::Move(const FInputActionValue& value)
{
	const FVector2D movement = value.Get<FVector2D>();
	const FRotator rotation = GetController()->GetControlRotation();
	const FRotator yawRotation = FRotator(0.0f, rotation.Yaw, 0.0f);
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	UE_LOG(LogTemp, Warning, TEXT("movement: %f %f"), movement.X, movement.Y);
	AddActorLocalOffset(forwardDirection * movement.Y * deltaTime * Speed);
}
