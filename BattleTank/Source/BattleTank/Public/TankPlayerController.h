// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
	
	// Moving the barrel so that a shot would hit where the crosshair intersects the world.
	void AimTowardsCrosshair();

	// Returns the OutHitLocation
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// Input the ScreenLocation and Returns the CameraWorldLocation and the LookDirection to the input.
	bool GetLookDirection(FVector2D ScreenLocation,FVector& CameraWorldLocation, FVector& LookDirection) const;

	// From the CameraWorldLocation and LookDirectiion, returns the HitResult.
	bool GetLookVectorHitLocation(FHitResult& HitResult, FVector CameraWorldLocation, FVector LookDirectiion) const;
};