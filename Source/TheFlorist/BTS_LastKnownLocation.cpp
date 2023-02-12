// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_LastKnownLocation.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_LastKnownLocation::UBTS_LastKnownLocation(){
    NodeName = TEXT("update last known location");
}

void UBTS_LastKnownLocation::TickNode(UBehaviorTreeComponent& OwnerComp, 
        uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(player){
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
                    player->GetActorLocation());
    }
} 