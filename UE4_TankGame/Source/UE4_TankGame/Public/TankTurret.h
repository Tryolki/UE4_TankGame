// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
class UTankBarrel;
UCLASS()
class UE4_TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void ElevateTurret(float RelativeTurretSpeed, float RelativeBarrelSpeed);
	void SetBarrelReference(UTankBarrel * Barrel);
	
	
};
