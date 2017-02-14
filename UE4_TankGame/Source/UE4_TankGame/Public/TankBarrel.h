// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class UE4_TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateBarrel(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreePerSecond = 20.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevation = 40.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevation = 0.f;
};
