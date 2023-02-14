// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnBasedEnemy.h"

#include "AbilityComponent.h"
#include "HealthStatusComponent.h"

ATurnBasedEnemy::ATurnBasedEnemy(){
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATurnBasedEnemy::BeginPlay(){
    Super::BeginPlay();
    
    //set the tag here and then update it at the end of turns / when taking damamge
    SetCombatMoodTag(); 
}

void ATurnBasedEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

ECombatMood ATurnBasedEnemy::GetCurrentMood(){
    if(!GetHealthComponent()) return ECombatMood::aggro;

	switch(GetHealthComponent()->GetCurrentState()){
		case EHealthState::dying:
			UE_LOG(LogTemp, Display, TEXT("mood: scared"));
			return ECombatMood::scared;
		case EHealthState::bloodied:
		UE_LOG(LogTemp, Display, TEXT("mood: defensive"));
			return ECombatMood::defence;
		default:
			UE_LOG(LogTemp, Display, TEXT("mood: aggresive"));
			return ECombatMood::aggro;
	}
}

void ATurnBasedEnemy::SetCombatMoodTag(){
	int dieRoll = 1 + (std::rand() % 20);
	switch(GetCurrentMood()){
		case ECombatMood::scared:
			dieRoll += 10;
			break;
		case ECombatMood::defence:
			dieRoll += 5;
			break;
		default:
			dieRoll += 0;
	}
	//UE_LOG(LogTemp, Display, TEXT("Updating tag, dice roll after mods = %i"), dieRoll);   
	
	FName combatMood;
	if(dieRoll >= 24){
		combatMood = TEXT("Flee");
		UE_LOG(LogTemp, Display, TEXT("new intention: flee"));
	}
	else if((dieRoll > 15) && (dieRoll <=23)){
		combatMood = TEXT("Defend");
		UE_LOG(LogTemp, Display, TEXT("new intention: defend"));
	}
	else{
		combatMood = TEXT("Attack");
		UE_LOG(LogTemp, Display, TEXT("new intention: attack"));
	}

	Tags.Empty();
	Tags.Add(combatMood);
}

bool ATurnBasedEnemy::UseSpecialAbility(EAbilityType abilType, ATurnBasedPawn* target){
    if(!GetAbilityComponent()) return false;

	int abilityIndex;
	if(GetAbilityComponent()->GetAbilityByType(abilType, abilityIndex)){
		UAbility* ability = GetAbilityComponent()->GetAbilityArray()[abilityIndex];
		if(ability){
			if((GetAbilityComponent()->GetCurrentPower() >= ability->cost) && (ability->cooldownRemain == 0)){
				//UE_LOG(LogTemp, Display, TEXT("Using ability (TBPawn)"));
				SetIntent(ability->name.ToString());
				
				switch(abilType){
					case EAbilityType::buff:
						GetAbilityComponent()->AddEffect(ability, true);
						break;
					case EAbilityType::damage:
						GetAbilityComponent()->UseDamageAbility(ability, target, this);
						break;
					case EAbilityType::debuff:
						target->GetAbilityComponent()->AddEffect(ability, false);
						break;
					case EAbilityType::heal:
						UseHealingAbility(ability);
						break;
				}

				ability->StartCooldownPeriod();
				GetAbilityComponent()->ReduceCurrentPower(ability->cost);

				return true;
			}
			UE_LOG(LogTemp, Display, TEXT("pawn cannot afford ability / ability is on cooldown (TBPawn)"));
		}
		UE_LOG(LogTemp, Display, TEXT("unable to cast relevent ability (TBPawn)"));
		return false;
	}
	UE_LOG(LogTemp, Display, TEXT("pawn has no relevent ability (TBPawn)"));
	return false;
}

void ATurnBasedEnemy::DealsDamage(AActor* target, float damage){
    Super::DealsDamage(target, damage);

    ATurnBasedEnemy* enemyPawn = Cast<ATurnBasedEnemy>(target);
    if(enemyPawn){
        enemyPawn->SetCombatMoodTag();
    }
}