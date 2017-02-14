// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4_TankGame.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

void ATank::SetBarrelReference(UTankBarrel * BarrelComponent)
{
	TankAimingComponent->SetBarrelReference(BarrelComponent);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *BarrelComponent->GetName());
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


