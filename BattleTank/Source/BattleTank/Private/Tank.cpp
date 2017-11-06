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
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSeconds;
	if (barrel && isReloaded)
	{
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
		FRotator startRotation = barrel->GetSocketRotation(FName("Projectile"));

		auto projectile = GetWorld()->SpawnActor<AProjectile>(projectileBlueprint, startLocation, startRotation);

		projectile->LaunchProjectile(LaunchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector hitLocation)
{
	if (!tankAimingComponent)
	{
		return;
	}

	tankAimingComponent->AimAt(hitLocation, LaunchSpeed);
}

