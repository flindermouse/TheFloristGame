// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_OffensiveAbility.h"

#include "Ability.h"
#include "TurnAI.h"
#include "TurnBasedEnemy.h"
#include "TurnBasedPawn.h"
#include "Kismet/GameplayStatics.h"

UBTT_OffensiveAbility::UBTT_OffensiveAbility(){
    NodeName = TEXT("Use Buff");
}

EBTNodeResult::Type UBTT_OffensiveAbility::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedEnemy* enemy = Cast<ATurnBasedEnemy>(enemyAI->GetPawn());
            if(enemy){
                ATurnBasedPawn* player = Cast<ATurnBasedPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
                if(player){
                    //UE_LOG(LogTemp, Display, TEXT("Enemy attempting to use special damage (UBTT_OffensiveAbility)"));
                    if(enemy->UseSpecialAbility(EAbilityType::damage, player)){
                        return EBTNodeResult::Succeeded;
                    }
                    else{
                        return EBTNodeResult::Failed;
                    }
                }
                UE_LOG(LogTemp, Display, TEXT("can't cast player (UBTT_OffensiveAbility)"));
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (UBTT_OffensiveAbility)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (UBTT_OffensiveAbility)"));
    }        

    return EBTNodeResult::Failed;                             
}

