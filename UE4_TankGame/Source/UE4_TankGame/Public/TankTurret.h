// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
class UTankBarrel;
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class UE4_TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeTurretSpeed, float RelativeBarrelSpeed);
	void SetBarrelReference(UTankBarrel * Barrel);
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreePerSecond = 20.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxElevation = 90.f;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MinElevation = -90.f;
private:
	UTankBarrel * BarrelComponent;
};
