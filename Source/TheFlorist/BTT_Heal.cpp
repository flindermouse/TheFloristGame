// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Heal.h"

#include "Ability.h"
#include "TurnAI.h"
#include "TurnBasedEnemy.h"

UBTT_Heal::UBTT_Heal(){
    NodeName = TEXT("Heal");
}

EBTNodeResult::Type UBTT_Heal::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedEnemy* enemy = Cast<ATurnBasedEnemy>(enemyAI->GetPawn());
            if(enemy){
                //UE_LOG(LogTemp, Display, TEXT("Enemy attempting to heal (BTT_Heal)"));
                if(enemy->UseSpecialAbility(EAbilityType::heal, enemy)){
                    return EBTNodeResult::Succeeded;
                }
                else{
                    return EBTNodeResult::Failed;
                }
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_Heal)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_Heal)"));
    }        

    return EBTNodeResult::Failed;                             
}