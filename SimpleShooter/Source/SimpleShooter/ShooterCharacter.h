// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "ShooterCharacter.generated.h"

class UInputAction;
class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* InputMappingContext;
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* LookRateAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.0f;

	UPROPERTY()
	AGun* Gun;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void LookRate(const FInputActionValue& value);
	void Jump() override;
	void Shoot(const FInputActionValue& value);
};
