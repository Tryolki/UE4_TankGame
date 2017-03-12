// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "UE4_TankGame/Public/TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = GetPlayerController();
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
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if(AimingComponent->GetFireState() ==  EFiringState::VE_Locked)
			AimingComponent->Fire();
	}


}

ATank* ATankAIController::GetPlayerController() const
{
	auto playerControllerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerControllerPawn)
		return nullptr;
	return Cast<ATank>(playerControllerPawn);
}
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	auto PossessedEnemy = Cast<ATank>(InPawn);
	if (!ensure(PossessedEnemy)) { return; }
	PossessedEnemy->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedObjectDeath);

}

void ATankAIController::OnPossedObjectDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s death"), *GetOwner()->GetName());
}


