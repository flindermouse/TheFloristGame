// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


void UAbility::StartCooldownPeriod(){
    cooldownRemain = cooldownTotal;
}

void UAbility::DecrementCooldownRemain(){
    if(cooldownRemain != 0){
        cooldownRemain -= 1;
    }
}

void UAbility::ResetCooldownRemain(){
    cooldownRemain = 0;
}

void UAbility::StartDuration(){
    durationRemain = durationTotal;
}

void UAbility::DecrementDurationRemain(){
    if(durationRemain != 0){
        durationRemain -= 1;
    }
}

void UAbility::PlayAbilityVFX(AActor* target){
    if (abilityVFX){
        //UE_LOG(LogTemp, Display, TEXT("found ability vfx (UAb)"));
        if(target){
            //UE_LOG(LogTemp, Display, TEXT("found target (UAb)"));
            if(target->GetWorld()){
                //UE_LOG(LogTemp, Display, TEXT("found world, attempting spawn vfx (UAb)"));
                UNiagaraComponent* vfxComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(target->GetWorld(), abilityVFX, 
                                                                target->GetActorLocation(), target->GetActorRotation());
            }
            else{
                UE_LOG(LogTemp, Display, TEXT("unable to find world (UAb)"));
            }
        }
        else{
            UE_LOG(LogTemp, Display, TEXT("no target (UAb)"));
        }
	}
    else{
        UE_LOG(LogTemp, Display, TEXT("No vfx for ability %s found (UAb)"), *name.ToString());
    }
}