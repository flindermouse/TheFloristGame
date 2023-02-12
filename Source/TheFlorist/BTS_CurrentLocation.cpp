// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_CurrentLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_CurrentLocation::UBTS_CurrentLocation(){
    NodeName = TEXT("update current location");
}

void UBTS_CurrentLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
					        float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);    

    APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(player){
        if(OwnerComp.GetAIOwner()){
            if(OwnerComp.GetAIOwner()->LineOfSightTo(player)){
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),
                    player->GetActorLocation());
            }
            else{
                OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
            }
        }   
        
    }
}