// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedPC.h"

#include "TimerManager.h"

void ATurnBasedPC::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner){
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UE_LOG(LogTemp, Display, TEXT("game end (TBPC)"));

    if(bIsWinner){
        // TODO
    }
    else{
        //TODO: Make this manual restart via UI
        GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, 3);
    }
}

