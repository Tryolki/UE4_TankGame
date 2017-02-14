// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class UE4_TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f; // 1000 m/s

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelComponent);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret * TurretComponent);

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UTankBarrel* Barrel = nullptr;
};
