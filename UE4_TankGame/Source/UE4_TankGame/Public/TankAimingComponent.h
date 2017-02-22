// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM(BlueprintType)
enum class EFiringState : uint8
{
	VE_Locked 	UMETA(DisplayName = "Lock"),
	VE_Aiming 	UMETA(DisplayName = "Aim"),
	VE_Reloading 	UMETA(DisplayName = "Reload")

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel * TankBarrel, UTankTurret * TankTurret);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void MoveBarrelTowards(const FVector & AimDirection);
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState AimingState = EFiringState::VE_Reloading;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
