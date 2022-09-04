// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasicPawn
{
	GENERATED_BODY()

public:
	//Constructor:
	ATank();

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* TankSpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* TankCamera;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TankSpeed = 200.f;
	UPROPERTY(EditAnywhere, Category="Movement")
	float TankTurnRate = 45.f;

	void Move(float Value);
	void Turn(float Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
