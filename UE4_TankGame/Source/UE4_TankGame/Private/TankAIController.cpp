// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "UE4_TankGame/Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledAITank = GetControlledTank();
	PlayerTank = GetPlayerController();
	if (!ControlledAITank)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't find tank AI controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank name: %s"), *ControlledAITank->GetName());
	}
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Didn't find player controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player controller. Tank name: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		ControlledAITank->AimAt(PlayerTank->GetActorLocation());
		//ControlledAITank->Fire();
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

