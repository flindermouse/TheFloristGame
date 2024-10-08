// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	//start at max power
	currentPower = maxPower;
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UAbilityComponent::GetPowerPercent() const{
	return currentPower / maxPower;
}

void UAbilityComponent::RegeneratePower(bool useDefaultRate, float regenRate){
	if(useDefaultRate){
		regenRate = powerRegenRate;
	}

	currentPower += regenRate;
	if(currentPower > maxPower){
		currentPower = maxPower;
	}
}

bool UAbilityComponent::GetAbilityByType(EAbilityType targetType, int &outIndex){
	for(int i = 0; i < abilities.Num(); i++){
		if(abilities[i]->type == targetType){
			outIndex = i;
			return true;
		}
	}
	return false;
}

bool UAbilityComponent::GetAbilityByName(FName abilName, int &outIndex){
	for(int i = 0; i < abilities.Num(); i++){
		if(abilities[i]->name.IsEqual(abilName)){
			outIndex = i;
			return true;
		}
	}
	return false;
}

void UAbilityComponent::DecrementAllCooldowns(){
	for(UAbility* abil : abilities){
		abil->DecrementCooldownRemain();
	}
}

void UAbilityComponent::ResetCooldown(int abilInd){
	UAbility* ability = abilities[abilInd];
	if(ability){
		ability->ResetCooldownRemain();
	}
}

void UAbilityComponent::AddAbility(UAbility* newAbility){
	abilities.Add(newAbility);
}

void UAbilityComponent::RemoveAbility(UAbility* oldAbility){
	abilities.Remove(oldAbility);
}

void UAbilityComponent::AddEffect(UAbility* ability, bool isBuff){
	if(ability){
		ability->StartDuration();
		ability->PlayAbilityVFX(GetOwner());

		if(isBuff){
			buffs.Add(ability->attribute, ability);
		}
		else{
			debuffs.Add(ability->attribute, ability);
		}
	}
	else{
		UE_LOG(LogTemp, Display, TEXT("Effect not added (UAbComp)"));
	}
}

void UAbilityComponent::RemoveEffect(ETargetAttribute attribute, bool isBuff){
	if(isBuff){
		if(buffs.Contains(attribute)){
			buffs.Remove(attribute);
		}
	}
	else{
		if(debuffs.Contains(attribute)){
			debuffs.Remove(attribute);
		}
	}
}

void UAbilityComponent::CheckAndRemoveLapsedEffects(){
	//TODO (update to remove multiple effects at the same time)
	ETargetAttribute toRemove = ETargetAttribute::none;
	for(TPair<ETargetAttribute, UAbility*> pair : buffs){
		if(pair.Value->durationRemain == 0){
			UE_LOG(LogTemp, Display, TEXT("removing %s (UAbComp)"), *pair.Value->name.ToString());
			toRemove = pair.Key;
			break;
		}
	}
	if(toRemove != ETargetAttribute::none){
		RemoveEffect(toRemove, true);
		toRemove = ETargetAttribute::none;
	}

	for(TPair<ETargetAttribute, UAbility*> pair : debuffs){
		if(pair.Value->durationRemain == 0){
			UE_LOG(LogTemp, Display, TEXT("removing %s (UAbComp)"), *pair.Value->name.ToString());
			toRemove = pair.Key;
			break;
		}
	}
	if(toRemove != ETargetAttribute::none){
		RemoveEffect(toRemove, false);
	}
}

void UAbilityComponent::DecrementAllEffectDurations(){
	for(TPair<ETargetAttribute, UAbility*> pair : buffs){
		UE_LOG(LogTemp, Display, TEXT("decrement duration of %s (UAbComp)"), *pair.Value->name.ToString());
		pair.Value->DecrementDurationRemain();
	}
	for(TPair<ETargetAttribute, UAbility*> pair : debuffs){
		UE_LOG(LogTemp, Display, TEXT("decrement duration of %s (UAbComp)"), *pair.Value->name.ToString());
		pair.Value->DecrementDurationRemain();
	}
}

float UAbilityComponent::AdjustAttribute(ETargetAttribute attribute, float base){
	if(buffs.Contains(attribute)){
		base = base * buffs[attribute]->magnitude;
	}
	if(debuffs.Contains(attribute)){
		base = base * debuffs[attribute]->magnitude;
	}
	return base;
}

void UAbilityComponent::UseDamageAbility(UAbility* ability, AActor* target, AActor* instigator){
    AController* controller = instigator->GetInstigatorController();
    if(!target || !controller) return;

	//TODO: Add damage types
	UGameplayStatics::ApplyDamage(target, ability->damageAmount, controller, instigator, 
						UDamageType::StaticClass());
	ability->PlayAbilityVFX(target);

    if(ability->durationTotal > 0){
        //TODO: ongoing damage
    }
}