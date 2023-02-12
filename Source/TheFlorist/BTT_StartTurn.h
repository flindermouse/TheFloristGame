// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTT_StartTurn.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API UBTT_StartTurn : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_StartTurn();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
	
};
