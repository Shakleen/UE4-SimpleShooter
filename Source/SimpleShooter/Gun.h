// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool GunTrace(FHitResult &Hit, FVector &ShotDirection);
	AController *GetOwnerController() const;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent *Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase *MuzzleSound = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem *HitParticles = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase *HitSound = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange = 1000.f;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 10.f;
};
