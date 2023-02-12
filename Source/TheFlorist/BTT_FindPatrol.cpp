// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindPatrol.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTT_FindPatrol::UBTT_FindPatrol(){
    NodeName = TEXT("find random patrol");
}

EBTNodeResult::Type UBTT_FindPatrol::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory){
    float patrolRad = 350.f;
    
    if(OwnerComp.GetAIOwner()){
        FNavLocation patrolPoint;
        const UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
        bool gotPatrol = navSys->GetRandomReachablePointInRadius(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), 
                                    patrolRad, patrolPoint);
        
        if(gotPatrol){
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), patrolPoint.Location);
        }
        else{
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), 
                                                    OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
        }

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}