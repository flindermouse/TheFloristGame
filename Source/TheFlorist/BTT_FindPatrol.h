// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTT_FindPatrol.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API UBTT_FindPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_FindPatrol();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
	
};
