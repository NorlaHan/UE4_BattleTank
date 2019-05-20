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

    if (GetSightRayHitLocation(HitLocation))    // Has "Side-effect", is going to line trace.
    {                
        // HitLocation = GetSightRayHitLocation();
        UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString());
        // TODO Tell controlled tank to aim at this point
    }
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const   // make no sense now, but it's all over the engine
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY; // Out parameter
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto SCreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation,ViewportSizeY*CrossHairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("Crosshair coordination : %s"), *SCreenLocation.ToString());

    // "De-projection"  the screen position of the crosshair to a direction
    // Line-trace along that look direction, and see what we hit (up to max range)
    
    OutHitLocation = FVector(1.0f);

    FVector PlayerCameraLocation;   // OUT Parameter
    FRotator PlayerCameraRotaion;   // OUT Parameter
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerCameraLocation,PlayerCameraRotaion);
    //UE_LOG(LogTemp, Warning, TEXT("Camera Location : %s, Rotator : %s"), *PlayerCameraLocation.ToString(), *PlayerCameraRotaion.ToString());
        
    FHitResult HitResult;   // OUT Parameter
    FVector LTEnd = (PlayerCameraLocation + PlayerCameraRotaion.Vector()*5000);
    FCollisionObjectQueryParams TraceObjectParameters(ECollisionChannel::ECC_PhysicsBody);
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetControlledTank());
    

    GetWorld()->LineTraceSingleByObjectType
    (
        HitResult, 
        PlayerCameraLocation, 
        LTEnd, 
        TraceObjectParameters, 
        TraceParameters
    );
    AActor* ActorHit = HitResult.GetActor();
    OutHitLocation = HitResult.Location;

    if (!ActorHit)
    {
        return false;
    }
    else
    {
        UE_LOG(LogTemp,Warning,TEXT("%s is in range"), *ActorHit->GetName());
    }
    
    return true;
}
