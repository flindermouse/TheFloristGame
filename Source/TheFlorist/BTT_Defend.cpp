// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Defend.h"

#include "TurnAI.h"
#include "TurnBasedPawn.h"

UBTT_Defend::UBTT_Defend(){
    NodeName = TEXT("Defend");
}

EBTNodeResult::Type UBTT_Defend::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(enemyAI->GetPawn());
            if(enemy){
                //UE_LOG(LogTemp, Display, TEXT("Enemy Defending (BTT_Defend)"));
                enemy->Defend();
                return EBTNodeResult::Succeeded;
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_Defend)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_Defend)"));
    }

    return EBTNodeResult::Failed;
}