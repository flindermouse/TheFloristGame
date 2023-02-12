// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "TurnAI.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API ATurnAI : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
	void UpdateTurnOnBlackboard(bool isPlayerTurn);

	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* tbTree;
};
