// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_TankGame.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement component"));
	MovementComponent->bAutoActivate = false;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile collision"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	LaunchBlast->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::LaunchProjectile(float Speed)
{
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

