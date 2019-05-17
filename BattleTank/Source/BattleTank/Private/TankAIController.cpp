// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
//#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    //ATank* ControlledTank = GetControlledTank();
    ATank* PlayerTank = GetPlayerTank();

    if (!PlayerTank)
    {
        UE_LOG(LogTemp,Warning,TEXT("Player Tank not found!"));
    }
    else
    {
        //UE_LOG(LogTemp,Warning,TEXT("%s ,Finds player : "),*GetOwner()->GetName());
        UE_LOG(LogTemp,Warning,TEXT("AI ,Finds player : %s"),*PlayerTank->GetName());
        if (this->GetOwner() == nullptr)
        {
            UE_LOG(LogTemp,Warning,TEXT("GetOwner() fails"));
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("%s"),*this->GetOwner()->GetName());
        }       
    }
}


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn){return nullptr;}

    return Cast<ATank>(PlayerPawn);
}