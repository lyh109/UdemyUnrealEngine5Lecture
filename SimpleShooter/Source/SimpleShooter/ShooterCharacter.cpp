// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gun.h"
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
	
	static ConstructorHelpers::FObjectFinder<UInputAction>IA_MOVE_FORWARD(TEXT("/Game/Input/IA_Move.IA_Move"));
	if (IA_MOVE_FORWARD.Succeeded())
	{
		MoveAction = IA_MOVE_FORWARD.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK(TEXT("/Game/Input/IA_Look.IA_Look"));
	if (IA_LOOK.Succeeded())
	{
		LookAction = IA_LOOK.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_LOOK_RATE(TEXT("/Game/Input/IA_LookRate.IA_LookRate"));
	if (IA_LOOK_RATE.Succeeded())
	{
		LookRateAction = IA_LOOK_RATE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>IA_JUMP(TEXT("/Game/Input/IA_Jump.IA_Jump"));
	if (IA_JUMP.Succeeded())
	{
		JumpAction = IA_JUMP.Object;
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

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
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
		 EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Move);
		 EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Look);
		 EnhancedInputComponent->BindAction(LookRateAction, ETriggerEvent::Triggered, this, &AShooterCharacter::LookRate);
		 EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::Jump);
	 }
}

void AShooterCharacter::Move(const FInputActionValue& value)
{
	const FVector2D movement = value.Get<FVector2D>();
	AddMovementInput(GetActorRightVector() * movement.X + GetActorForwardVector() * movement.Y);
}

void AShooterCharacter::Look(const FInputActionValue& value)
{
	const FVector2D movement = value.Get<FVector2D>();

	AddControllerYawInput(movement.X);
	AddControllerPitchInput(movement.Y);
}

void AShooterCharacter::LookRate(const FInputActionValue& value)
{
	const FVector2D movement = value.Get<FVector2D>();

	AddControllerYawInput(movement.X * RotationRate * GetWorld()->GetDeltaSeconds());
	AddControllerPitchInput(movement.Y * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Jump()
{
	Super::Jump();
}
