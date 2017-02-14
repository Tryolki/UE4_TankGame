// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel * component);
	void SetTurretReference(UTankTurret * component);
	void MoveBarrelTowards(const FVector & AimDirection);
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
