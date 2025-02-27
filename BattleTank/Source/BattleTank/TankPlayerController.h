// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    ATank* GetControlledTank() const;

    // start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
    void AimTowardsCrosshair();

    bool GetSightRayHitLocation(FVector &HitLocation) const;

    bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

    bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = .5f;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = .33333f;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000.0f;
};
