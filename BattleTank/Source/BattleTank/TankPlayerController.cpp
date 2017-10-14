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
		UE_LOG(LogTemp, Warning, TEXT("hitLocation: %s"), *hitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& outHitLocation) const
{
	FVector2D screenLocation = GetCrosshairScreenLocation();

	FVector worldDirection;

	if (GetLookDirection(screenLocation, worldDirection))
	{
		// TODO: From here down is WIP
		FVector eyesLocation;
		FRotator eyesRotation;

		PlayerCameraManager->GetActorEyesViewPoint(eyesLocation, eyesRotation);

		FVector endPoint = eyesLocation + (worldDirection * 100000.0f);

		FCollisionQueryParams queryParams = FCollisionQueryParams(FName(TEXT("Crosshair Line Trace")), true, this);
		FHitResult hitOut = FHitResult(ForceInit);

		if (GetWorld()->LineTraceSingleByChannel(hitOut, eyesLocation, endPoint, ECC_Pawn, queryParams))
		{
			if (hitOut.bBlockingHit)
			{
				outHitLocation = hitOut.Location;
				return true;
			}
		}
	}

	outHitLocation = FVector(1.0f);
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
