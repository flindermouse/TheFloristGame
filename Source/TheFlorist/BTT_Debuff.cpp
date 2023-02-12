// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Debuff.h"

#include "Ability.h"
#include "TurnAI.h"
#include "TurnBasedPawn.h"
#include "Kismet/GameplayStatics.h"


UBTT_Debuff::UBTT_Debuff(){
    NodeName = TEXT("Use Debuff");
}

EBTNodeResult::Type UBTT_Debuff::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner()){
        ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
        if(enemyAI){
            ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(enemyAI->GetPawn());
            if(enemy){
                ATurnBasedPawn* player = Cast<ATurnBasedPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
                if(player){
                    UE_LOG(LogTemp, Display, TEXT("Enemy attempting to debuff (BTT_Debuff)"));
                    if(enemy->UseSpecialAbility(EAbilityType::debuff, player)){
                        return EBTNodeResult::Succeeded;
                    }
                    else{
                        return EBTNodeResult::Failed;
                    }
                }
                UE_LOG(LogTemp, Display, TEXT("can't cast player (BTT_Debuff)"));   
            }
            UE_LOG(LogTemp, Display, TEXT("can't cast pawn (BTT_Debuff)"));
        }
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (BTT_Debuff)"));
    }        

    return EBTNodeResult::Failed;                             
}