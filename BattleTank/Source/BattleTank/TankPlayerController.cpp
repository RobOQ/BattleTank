// Copyright 2017 Robert O'Quinn

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

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
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	FVector2D screenLocation = GetCrosshairScreenLocation();

	FVector worldDirection;

	if (GetLookDirection(screenLocation, worldDirection))
	{
		return GetLookVectorHitLocation(worldDirection, outHitLocation);
	}

	outHitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const
{
	FVector cameraWorldLocation;

	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, cameraWorldLocation, lookDirection);
}

FVector2D ATankPlayerController::GetCrosshairScreenLocation() const
{
	int32 viewportSizeX;
	int32 viewportSizeY;
	GetViewportSize(viewportSizeX, viewportSizeY);

	return FVector2D(viewportSizeX * crossHairXLocation, viewportSizeY * crossHairYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		return true;
	}

	return false;
}
