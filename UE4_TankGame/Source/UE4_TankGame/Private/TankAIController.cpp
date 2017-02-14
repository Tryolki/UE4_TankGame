// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "UE4_TankGame/Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledAITank = GetControlledTank();
	PlayerController = GetPlayerController();
	if (!ControlledAITank)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't find tank AI controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank name: %s"), *ControlledAITank->GetName());
	}
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't find player controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player controller. Tank name: %s"), *PlayerController->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetPlayerController();
	if (PlayerTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s aim at %s"), *GetControlledTank()->GetName(), *PlayerTank->GetName());
		//GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}


}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerController() const
{
	auto playerControllerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerControllerPawn)
		return nullptr;
	return Cast<ATank>(playerControllerPawn);
}

