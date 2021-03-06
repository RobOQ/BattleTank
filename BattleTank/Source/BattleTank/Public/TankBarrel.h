// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1.0f is max downward speed, and +1.0f is max upward speed
	void Elevate(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float maxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float minElevationInDegrees = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float maxElevationInDegrees = 40.0f;
};
