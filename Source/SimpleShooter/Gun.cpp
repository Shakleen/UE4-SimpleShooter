// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(OUT HitResult, OUT ShotDirection);

	if (bSuccess && HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			HitResult.Location,
			ShotDirection.Rotation());

		UGameplayStatics::SpawnSoundAtLocation(this, HitSound, HitResult.Location);

		if (HitResult.GetActor())
		{
			AController *OwnerController = GetOwnerController();
			if (!OwnerController)
				return;

			HitResult.GetActor()->TakeDamage(DamageAmount, DamageEvent, OwnerController, GetOwner());
			FPointDamageEvent DamageEvent(DamageAmount, HitResult, ShotDirection, nullptr);
		}
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGun::GunTrace(FHitResult &Hit, FVector &ShotDirection)
{
	AController *OwnerController = GetOwnerController();
	if (!OwnerController)
		return false;

	FVector StartLocation;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(OUT StartLocation, OUT Rotation);

	ShotDirection = -Rotation.Vector();
	FVector EndLocation = StartLocation + Rotation.Vector() * MaxRange;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Params);

	return bSuccess;
}

AController *AGun::GetOwnerController() const
{
	APawn *GunOwner = Cast<APawn>(GetOwner());
	if (!GunOwner)
		return nullptr;

	AController *OwnerController = GunOwner->GetController();
	if (!OwnerController)
		return nullptr;

	return OwnerController;
}
