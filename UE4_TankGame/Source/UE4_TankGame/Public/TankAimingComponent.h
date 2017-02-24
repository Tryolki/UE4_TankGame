// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UTankBarrel;
class UTankTurret;
class AProjectile;
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

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f; // 1000 m/s

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;


	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	void AimAt(FVector HitLocation);
	void MoveBarrelTowards(const FVector & AimDirection);
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState AimingState = EFiringState::VE_Aiming;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	double LastFireTime = 0;
};
