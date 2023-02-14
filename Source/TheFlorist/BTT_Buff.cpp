// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Buff.h"

#include "Ability.h"
#include "TurnAI.h"
#include "TurnBasedEnemy.h"

UBTT_Buff::UBTT_Buff(){
    NodeName = TEXT("Use Buff");
}

EBTNodeResult::Type UBTT_Buff::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedEnemy* enemy = Cast<ATurnBasedEnemy>(enemyAI->GetPawn());
            if(enemy){
                //UE_LOG(LogTemp, Display, TEXT("Enemy attempting to buff (BTT_Buff)"));
                if(enemy->UseSpecialAbility(EAbilityType::buff, enemy)){
                    return EBTNodeResult::Succeeded;
                }
                else{
                    return EBTNodeResult::Failed;
                }
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_Buff)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_Buff)"));
    }        

    return EBTNodeResult::Failed;                             
}