// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnAI.h"

#include "HealthStatusComponent.h"
#include "TurnBasedGameMode.h"
#include "TurnBasedPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void ATurnAI::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);

}

void ATurnAI::UpdateTurnOnBlackboard(bool isPlayerTurn){
    if(GetBlackboardComponent()){
        if(isPlayerTurn){
            GetBlackboardComponent()->ClearValue(TEXT("AITurn"));
            UE_LOG(LogTemp, Display, TEXT("Switch to Player (TurnAI)"));
        }
        else{
            GetBlackboardComponent()->SetValueAsBool(TEXT("AITurn"), true);
            UE_LOG(LogTemp, Display, TEXT("Switch to AI (TurnAI)"));
        }
    }
}

bool ATurnAI::IsDead() const{
    ATurnBasedPawn* pawn = Cast<ATurnBasedPawn>(GetPawn());
    if(pawn){
        if(pawn->GetCurrentState() == EHealthState::dead){
            return true;
        }
        else{
            return false;
        }        
    }
    return true;
}

void ATurnAI::BeginPlay(){
    Super::BeginPlay();

    if(tbTree){
        RunBehaviorTree(tbTree);
        ATurnBasedGameMode* gameMode = GetWorld()->GetAuthGameMode<ATurnBasedGameMode>();
        if(gameMode){
            //TODO 
            UpdateTurnOnBlackboard(gameMode->GetIsPlayerTurn());  
        }           
    }
}