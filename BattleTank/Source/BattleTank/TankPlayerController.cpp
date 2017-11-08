// Copyright 2017 Robert O'Quinn

#include "TankPlayerController.h"
#include "Tank.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component in BeginPlay()"));
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
	if (GetControlledTank())
	{
		return;
	}

	FVector HitLocation; // Out parameter

	// TODO: If we don't hit anything with our collision trace,
	// should we leave the aim as-is, or should we return the aim
	// to the default (aim straight ahead)?
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	FVector2D ScreenLocation = GetCrosshairScreenLocation();

	FVector WorldDirection;

	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		return GetLookVectorHitLocation(WorldDirection, outHitLocation);
	}

	outHitLocation = FVector(0.0f);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

FVector2D ATankPlayerController::GetCrosshairScreenLocation() const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	return FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
