// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UE4_TANKGAME_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		int32 StartingHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float Armor = 0.25;

	UPROPERTY(VisibleAnywhere, Category = Health)
		int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float Speed = 0.25;
};
