// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerControlledTank = GetPlayerTank();
    if (nullptr == PlayerControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Player not possessing a tank"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Player possessing tank %s"), *(PlayerControlledTank->GetName()));
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetPlayerTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn)
    {
        return nullptr;
    }

    return Cast<ATank>(PlayerPawn);
}