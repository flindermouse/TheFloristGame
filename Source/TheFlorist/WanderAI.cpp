// Fill out your copyright notice in the Description page of Project Settings.


#include "WanderAI.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AWanderAI::BeginPlay(){
    Super::BeginPlay();

    if(behave){
        RunBehaviorTree(behave);        
    }
}