// Copyright 2017 Robert O'Quinn

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	if (!barrelToSet)
	{
		return;
	}

	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	if (!turretToSet)
	{
		return;
	}

	turret = turretToSet;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!barrel)
	{
		return;
	}

	FVector outLaunchVelocity = FVector(0.0f);
	FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
	
	auto haveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);

	// Calculate the outLaunchVelocity
	if (haveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!barrel || !turret)
	{
		return;
	}

	// Calculate difference between current barrel rotation and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	barrel->Elevate(deltaRotator.Pitch);

	auto yaw = deltaRotator.Yaw;
	yaw = FRotator::NormalizeAxis(yaw);
	turret->Rotate(yaw);
}
