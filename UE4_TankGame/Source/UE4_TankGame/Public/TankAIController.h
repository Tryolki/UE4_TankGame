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
	
private:
	ATank* PlayerTank;
	ATank* ControlledAITank;
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	ATank* GetControlledTank() const;
	ATank* GetPlayerController() const;
};
