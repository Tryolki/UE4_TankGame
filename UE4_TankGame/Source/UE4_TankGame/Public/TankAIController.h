// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	virtual void SetPawn(APawn* InPawn) override;
private:
	ATank* PlayerTank;
	ATank* ControlledAITank;
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	ATank* GetPlayerController() const;
	UPROPERTY(EditAnywhere, Category=Setup)
	float AcceptanceRadius = 3000.f;

	UFUNCTION()
	void OnPossedObjectDeath();
};
