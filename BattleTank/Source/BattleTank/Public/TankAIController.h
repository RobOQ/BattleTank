// Copyright 2017 Robert O'Quinn

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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
	ATank* GetPlayerTank() const;
	void AimAtPlayerTank();

	UPROPERTY(EditDefaultsOnly)
	float acceptanceRadius = 1500.0f;
};
