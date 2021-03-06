// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UE4_TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LaunchProjectile(float Speed);

	UFUNCTION(BlueprintCallable, Category = HitCollision)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestroyDelay = 10.f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 10.f;
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ExplocionForce = nullptr;

private:
	UProjectileMovementComponent* MovementComponent = nullptr;
	void OnTimerExpire();
};
