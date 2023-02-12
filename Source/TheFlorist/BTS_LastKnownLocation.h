// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "BTS_LastKnownLocation.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API UBTS_LastKnownLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_LastKnownLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
					float DeltaSeconds) override;	
	
};
