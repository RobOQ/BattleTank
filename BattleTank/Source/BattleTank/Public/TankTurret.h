// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1.0f is max downward speed, and +1.0f is max upward speed
	void Rotate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float minRotationInDegrees = 0.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float maxRotationInDegrees = 360.0f;
};
