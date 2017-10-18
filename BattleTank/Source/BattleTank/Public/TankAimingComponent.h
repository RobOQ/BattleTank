// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

// Handle's aiming the tank's barrel and turret
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* barrelToSet);

	// TODO Add SetTurretReference

	void AimAt(FVector hitLocation, float launchSpeed);

private:
	void MoveBarrelTowards(FVector aimDirection);

	UTankBarrel* barrel = nullptr;
};
