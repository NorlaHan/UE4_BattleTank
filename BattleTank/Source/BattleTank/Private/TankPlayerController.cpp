// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"
#include "DrawDebugHelpers.h"
#include "Math/TwoVectors.h"
#include "Engine/World.h"



    
// BeginPlay
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController NOT possessing a Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TankPlayerController possessing : %s"),*ControlledTank->GetName());
    }
}

// Tick
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
    if (!GetControlledTank()){return;}
    
    FVector HitLocation;    // Out parameter
    UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
    // Get world location of linetrace through crosshair
    GetSightRayHitLocation();
    // If it hits the landscape
        // Tell controlled tank to aim at this point
}

FVector ATankPlayerController::GetSightRayHitLocation() const
{
    FVector OutHitLocation;

    FVector PlayerCameraLocation;   // OUT Parameter
    FRotator PlayerCameraRotaion;   // OUT Parameter
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerCameraLocation,PlayerCameraRotaion);

    FHitResult HitResult;   // OUT Parameter
    GetWorld()->LineTraceSingleByObjectType
    (
        HitResult, 
        PlayerCameraLocation, 
        PlayerCameraLocation + PlayerCameraRotaion.Vector()*9999, 
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
        const FCollisionQueryParams & Params = FCollisionQueryParams::DefaultQueryParam
    );

    return OutHitLocation;
}
