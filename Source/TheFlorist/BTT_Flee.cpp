// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Flee.h"

#include "TurnAI.h"
#include "TurnBasedGameMode.h"
#include "TurnBasedPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_Flee::UBTT_Flee(){
    NodeName = TEXT("Flee");
}

EBTNodeResult::Type UBTT_Flee::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){
    //TODO: Flee
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    ATurnBasedGameMode* gameMode = GetWorld()->GetAuthGameMode
													<ATurnBasedGameMode>();
    if(gameMode){
        UE_LOG(LogTemp, Display, TEXT("Running away!"));
        gameMode->SetHasPlayerWon(true);
        gameMode->EndCombat(true); 

        if(OwnerComp.GetAIOwner()){
        //ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(OwnerComp.GetAIOwner()->GetPawn());
            ATurnAI* enemyAI = Cast<ATurnAI>(OwnerComp.GetAIOwner());
            if(enemyAI){
                ATurnBasedPawn* enemy = Cast<ATurnBasedPawn>(enemyAI->GetPawn());
                if(enemy){
                    // get ready for destruction + turn off collisions
                    enemy->DetachFromControllerPendingDestroy(); 
                    enemy->Destroy();
                    UE_LOG(LogTemp, Warning, TEXT("Pawn destroyed (UBTT_Flee)"))
                }
            }
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
