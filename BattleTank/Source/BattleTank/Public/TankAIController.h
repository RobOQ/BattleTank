// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	APawn* GetPlayerPawn() const;
	void AimAtPlayerTank();

	UTankAimingComponent* GetAimingComponent() const;

	UPROPERTY(EditDefaultsOnly)
	float acceptanceRadius = 1500.0f;
};
