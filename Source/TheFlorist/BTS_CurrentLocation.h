// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "BTS_CurrentLocation.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API UBTS_CurrentLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_CurrentLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
					float DeltaSeconds) override;	
	
};
