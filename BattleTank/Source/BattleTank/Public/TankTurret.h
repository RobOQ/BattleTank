// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1.0f is max downward speed, and +1.0f is max upward speed
	void Rotate(float relativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float maxDegreesPerSecond = 25.0f;
};
