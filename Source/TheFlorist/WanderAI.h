// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "WanderAI.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API AWanderAI : public AAIController
{
	GENERATED_BODY()

public:
	//virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* behave;

	APawn* player;
	
};
