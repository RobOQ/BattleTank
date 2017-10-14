// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;
	
	// Start the tank moving the barrel so that a shot would hit where the
	// crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& outHitLocation) const;

	UPROPERTY(EditAnywhere)
	float crossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float crossHairYLocation = 0.33333f;
};
