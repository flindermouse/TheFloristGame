// Fill out your copyright notice in the Description page of Project Settings.


#include "WanderAI.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

/*
void AWanderAI::Tick(float DeltaSeconds){
    Super::Tick(DeltaSeconds);
}
*/

void AWanderAI::BeginPlay(){
    Super::BeginPlay();

    player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(behave){
        RunBehaviorTree(behave);

        GetBlackboardComponent()->SetValueAsVector(TEXT("playerLoc"), 
                                    player->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("startLoc"), GetPawn()->
                                    GetActorLocation());
    }
}