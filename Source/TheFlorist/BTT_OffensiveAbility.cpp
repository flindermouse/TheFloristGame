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

    if(!OwnerComp.GetAIOwner()){
        UE_LOG(LogTemp, Display, TEXT("can't find ai controller (UBTT_OffensiveAbility)"));
        return EBTNodeResult::Failed; 
    }
    
    ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
    if(!enemyAI){
        UE_LOG(LogTemp, Display, TEXT("can't cast ai controller (UBTT_OffensiveAbility)"));
        return EBTNodeResult::Failed; 
    }
    
    ATurnBasedEnemy* enemy = Cast<ATurnBasedEnemy>(enemyAI->GetPawn());
    if(!enemy){
        UE_LOG(LogTemp, Display, TEXT("can't cast enemy pawn (UBTT_OffensiveAbility)"));
        return EBTNodeResult::Failed; 
    }
        
    ATurnBasedPawn* player = Cast<ATurnBasedPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(!player){
        UE_LOG(LogTemp, Display, TEXT("can't cast player (UBTT_OffensiveAbility)"));
        return EBTNodeResult::Failed; 
    }
    
    // use special ability checks if enemy has relevant ability & enough stamina to use it
    if(enemy->UseSpecialAbility(EAbilityType::damage, player)){
        // ability successfully used
        return EBTNodeResult::Succeeded;
    }
    else{
        // no ability or not enough stamina, return failed so AI can take a different action
        return EBTNodeResult::Failed;
    }                       
}

