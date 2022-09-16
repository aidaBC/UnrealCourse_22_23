// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    TankSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Tank Spring Arm"));
    TankSpringArm->SetupAttachment(RootComponent);

    TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    TankCamera->SetupAttachment(TankSpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );
        
        RotateTurret(HitResult.ImpactPoint);
    }

}

void ATank::Move(float Value)
{
    //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TankSpeed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TankTurnRate;
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}