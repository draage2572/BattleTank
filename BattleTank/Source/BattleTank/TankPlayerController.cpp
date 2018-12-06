// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Player controller not possesing a tank"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s!"), *(ControlledTank->GetName()));
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }

    FVector HitLocation;

    if (GetSightRayHitLocation(HitLocation))
    {
        GetControlledTank()->AimAt(HitLocation);
    }
    // get world location through crosshair
    // if it hits landscape
        // tell controlled tank to aim at this point
}
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
    HitLocation = FVector{ 1.f };

    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D{ ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation };
   
    // De-project the screen position of the crosshair in a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        if (GetLookVectorHitLocation(LookDirection, HitLocation))
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
        }
    }
    // Line trace along that look direction and see what we hit (up to max range)

    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + LookDirection * LineTraceRange;
    
    FHitResult HitResult;
    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility
    ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector{ 0.f };

    return false;
}

