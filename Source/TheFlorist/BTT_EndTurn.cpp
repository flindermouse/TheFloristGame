// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EndTurn.h"

#include "TurnAI.h"
#include "TurnBasedGameMode.h"
#include "TurnBasedPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTT_EndTurn::UBTT_EndTurn(){
    NodeName = TEXT("End Turn");
}

EBTNodeResult::Type UBTT_EndTurn::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory); 

     ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
    if(enemyAI){
        ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(enemyAI->GetPawn());
        if(enemy){
            //set mood for next turn
            enemy->SetCombatMoodTag();
            //decrement any active buff/debuff duration
	        enemy->DecrementEffectDurations();
        }
    }

    ATurnBasedGameMode* gameMode = GetWorld()->GetAuthGameMode
													<ATurnBasedGameMode>();
    if(gameMode){
        UE_LOG(LogTemp, Display, TEXT("Switch to Player (BTT_EndTurn)"));
        gameMode->EndTurn(); 

        ATurnBasedPawn* player = Cast<ATurnBasedPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        if(player){
            player->StartTurn();
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}