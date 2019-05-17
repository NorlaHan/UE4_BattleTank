// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


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


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}