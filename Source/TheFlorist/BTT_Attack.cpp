// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Attack.h"

#include "TurnAI.h"
#include "TurnBasedEnemy.h"
#include "TurnBasedPawn.h"
#include "Kismet/GameplayStatics.h"

UBTT_Attack::UBTT_Attack(){
    NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

    ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
    if(!enemyAI){
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_Attack)"));
        return EBTNodeResult::Failed;
    }

    ATurnBasedEnemy* enemy = Cast<ATurnBasedEnemy>(enemyAI->GetPawn());
    if(!enemy){
        UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_Attack)"));
        return EBTNodeResult::Failed;   
    }

    ATurnBasedPawn* player = Cast<ATurnBasedPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(!player){
        UE_LOG(LogTemp, Display, TEXT("can't get player (BTT_Attack)"));
        return EBTNodeResult::Failed;
    }

    //UE_LOG(LogTemp, Display, TEXT("Enemy Attacking (BTT_Attack)"));
    enemy->Attack(player);
    return EBTNodeResult::Succeeded;
}