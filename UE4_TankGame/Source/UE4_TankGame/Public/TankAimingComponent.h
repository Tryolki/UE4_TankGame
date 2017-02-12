// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//TODO Set reference to turret. SetTurretReference(UStaticMeshComponent * component)
	
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void SetBarrelReference(UStaticMeshComponent * component);
	void MoveBarrelTowards(const FVector & AimDirection);
private:
	UStaticMeshComponent* BarrelMeshComponent = nullptr;
};
