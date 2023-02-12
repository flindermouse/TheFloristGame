// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedGameMode.h"

#include "TurnAI.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

void ATurnBasedGameMode::EndTurn(){
    UE_LOG(LogTemp, Display, TEXT("Ending turn (TBGameMode)")); 
    //swap who's turn it is
    playerTurn = !playerTurn;

    for(ATurnAI* turnAI : TActorRange<ATurnAI>(GetWorld())){
        turnAI->UpdateTurnOnBlackboard(playerTurn);   
        break;
    }
}

void ATurnBasedGameMode::EndCombat(bool playerWon){
    UE_LOG(LogTemp, Warning, TEXT("Ending combat (TBGameMode)"));
    combatEnd = true;

    for(AController* control : TActorRange<AController>(GetWorld())){
        bool winner = false;
        if(control->IsPlayerController() == playerWon){
            winner = true;
            // if this is the player nad the player won, set true
            // if this isn't the player and the player lost, set true
        }
        control->GameHasEnded(control->GetPawn(), winner);
    }
}

void ATurnBasedGameMode::PawnKilled(APawn* dead){
    Super::PawnKilled(dead);

    UE_LOG(LogTemp, Display, TEXT("pawn killed"));

    APlayerController* pc = Cast<APlayerController>(dead->GetController());
    if(pc){ //if pc isn't null, it was the player killed
        combatEnd = true;
        EndCombat(playerWin);
    }

    for (ATurnAI* control : TActorRange<ATurnAI>(GetWorld())){
        if (!control->IsDead()) {
            return; //if any enemies are still alive, end here
        }
    }
    playerWin = true;
    EndCombat(playerWin);
}

void ATurnBasedGameMode::BeginPlay(){
    Super::BeginPlay();

    //TODO: allow other things (stats?) to affect who goes first
    int dieRoll = 1 + (std::rand() % 4);
    if(dieRoll <= 3){
        playerTurn = true;
        UE_LOG(LogTemp, Display, TEXT("Player starts"));
    }
    else{
        playerTurn = false;
        UE_LOG(LogTemp, Display, TEXT("AI starts"));
    }

    for(ATurnAI* turnAI : TActorRange<ATurnAI>(GetWorld())){
        turnAI->UpdateTurnOnBlackboard(playerTurn);   
        break;
    }
}
