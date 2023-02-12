// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StartTurn.h"

#include "TurnAI.h"
#include "TurnBasedPawn.h"

UBTT_StartTurn::UBTT_StartTurn(){
    NodeName = TEXT("Start Turn");
}

EBTNodeResult::Type UBTT_StartTurn::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(enemyAI->GetPawn());
            if(enemy){
                UE_LOG(LogTemp, Display, TEXT("Enemy Starting Turn (BTT_StartTurn)"));
                enemy->StartTurn();
                return EBTNodeResult::Succeeded;
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_StartTurn)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_StartTurn)"));
    }

    return EBTNodeResult::Failed;
}

