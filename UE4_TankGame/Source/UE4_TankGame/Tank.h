// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
class UTankBarrel;
class UTankTurret;
class AProjectile;
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class UE4_TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();

	//void AimAt(FVector HitLocation);

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
protected:

	UTankBarrel* Barrel = nullptr;
	double LastFireTime = 0;
};
