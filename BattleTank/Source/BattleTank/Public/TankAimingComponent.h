// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UStaticMeshComponent* barrelToSet);

	// TODO Add SetTurretReference

	void AimAt(FVector hitLocation, float launchSpeed);

private:
	void MoveBarrelTowards(FVector aimDirection);

	UStaticMeshComponent* barrel = nullptr;
};
