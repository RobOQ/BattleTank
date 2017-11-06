// Copyright 2017 Robert O'Quinn

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("[KOALA] ATank() constructor: %s"), *GetName());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[KOALA] ATank::BeginPlay(): %s"), *GetName());
}

void ATank::Fire()
{
	if (!ensure(barrel))
	{
		return;
	}

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator startRotation = barrel->GetSocketRotation(FName("Projectile"));

		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, startLocation, startRotation);

		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector hitLocation)
{
	if (!ensure(tankAimingComponent))
	{
		return;
	}

	tankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

