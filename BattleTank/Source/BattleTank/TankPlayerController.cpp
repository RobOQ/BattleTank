// Copyright 2017 Robert O'Quinn

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* controlledTank = GetControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play possessing %s"), *(controlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play not possessing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector hitLocation; // Out parameter

	if (GetSightRayHitLocation(hitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("hitLocation: %s"), *hitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	// TODO: Hook up this code
	//FCollisionQueryParams queryParams = FCollisionQueryParams(FName(TEXT("Crosshair Line Trace")), true, this);

	//FHitResult hitOut = FHitResult(ForceInit);

	//FVector eyesLocation;
	//FRotator eyesRotation;

	//PlayerCameraManager->GetActorEyesViewPoint(eyesLocation, eyesRotation);

	outHitLocation = FVector(1.0f);
	return false;
}
