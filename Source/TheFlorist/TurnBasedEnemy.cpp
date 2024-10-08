// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnBasedEnemy.h"

#include "AbilityComponent.h"
#include "Enemy.h"
#include "HealthStatusComponent.h"

ATurnBasedEnemy::ATurnBasedEnemy(){
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATurnBasedEnemy::BeginPlay(){
    Super::BeginPlay();
    
    //set the tag here and then update it at the end of turns
    SetCombatMoodTag(); 

	//get the skeletal mesh
	skelly = Cast<USkeletalMeshComponent>(GetRootComponent());
}

ECombatMood ATurnBasedEnemy::GetCurrentMood(){
    if(!GetHealthComponent()) return ECombatMood::aggro;

	// set the enemy's mood based on it's remaining health
	switch(GetHealthComponent()->GetCurrentState()){
		case EHealthState::dying:
			return ECombatMood::scared;
		case EHealthState::bloodied:
			return ECombatMood::defence;
		default:
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

	if(dieRoll >= 24){
		//UE_LOG(LogTemp, Display, TEXT("new intention: flee"));
		gameplayTags.Reset();
		gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("EnemyAction.Flee"))));
	}
	else if((dieRoll > 15) && (dieRoll <=23)){
		//UE_LOG(LogTemp, Display, TEXT("new intention: defend"));
		gameplayTags.Reset();
		gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("EnemyAction.Defend"))));
	}
	else{
		//UE_LOG(LogTemp, Display, TEXT("new intention: attack"));
		gameplayTags.Reset();
		gameplayTags.AddTag(FGameplayTag::RequestGameplayTag(FName(TEXT("EnemyAction.Attack"))));
	}
}

bool ATurnBasedEnemy::UseSpecialAbility(EAbilityType abilType, ATurnBasedPawn* target){
    if(!GetAbilityComponent()) return false;

	int abilityIndex;
	if(GetAbilityComponent()->GetAbilityByType(abilType, abilityIndex)){
		UAbility* ability = GetAbilityComponent()->GetAbilityArray()[abilityIndex];
		if(!ability){
			UE_LOG(LogTemp, Display, TEXT("unable to cast ability (TBEnemy)"));
			return false;
		}

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

			if(!skelly){
				UE_LOG(LogTemp, Display, TEXT("can't find mesh (TBEnemy)"));
				return true;
			}
			if(!enemyType){
				UE_LOG(LogTemp, Display, TEXT("can't find enemy type (TBEnemy)"));
				return true;
			}
			if(!enemyType->cast){
				UE_LOG(LogTemp, Display, TEXT("can't find animation (TBEnemy)"));
				return true;
			}

			skelly->PlayAnimation(enemyType->cast, false);
			return true;
		}
		UE_LOG(LogTemp, Display, TEXT("pawn cannot afford ability / ability is on cooldown (TBEnemy)"));
		return false;

	}
	UE_LOG(LogTemp, Display, TEXT("pawn has no relevent ability (TBEnemy)"));
	return false;
}

void ATurnBasedEnemy::Attack(AActor* target){
	Super::Attack(target);

	if(!skelly){
		UE_LOG(LogTemp, Display, TEXT("skeleton not found (TBEnemy)"));
		return;
	}
	if(!enemyType){
		UE_LOG(LogTemp, Display, TEXT("enemy type not found (TBEnemy)"));
		return;	
	}

	skelly->PlayAnimation(enemyType->attack, false);
}

void ATurnBasedEnemy::EndTurn(){
	Super::EndTurn();
	SetCombatMoodTag();
}

void ATurnBasedEnemy::PlayIdle(){
	if(!skelly) return;
	if(skelly->IsPlaying()) return;
	if(!enemyType) return;
	skelly->PlayAnimation(enemyType->idle, true);
}