// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedPawn.h"

#include "Ability.h"
#include "AbilityComponent.h"
#include "HealthStatusComponent.h"
#include "TurnBasedGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurnBasedPawn::ATurnBasedPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurnBasedPawn::BeginPlay()
{
	Super::BeginPlay();
	
	gameMode = GetWorld()->GetAuthGameMode<ATurnBasedGameMode>();	
	health = FindComponentByClass<UHealthStatusComponent>();
	abilities = FindComponentByClass<UAbilityComponent>();

	SetCombatMoodTag();
}

// Called every frame
void ATurnBasedPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurnBasedPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATurnBasedPawn::StartTurn(){
	//TODO: any pawn upkeep to go here

	if(abilities){ 
		//regenerate some stamina
		//abilities->RegeneratePower();

		//decrement the cooldown of any ability used
		abilities->DecrementAllCooldowns();

		//remove any buff/debuff that has reached 0 duration
		abilities->CheckAndRemoveLapsedEffects();
	}

	if(hasGuard){ //defending only lasts 1 round
		SetGuarding(false);
	}
}

void ATurnBasedPawn::Attack(AActor* target){
	//UE_LOG(LogTemp, Display, TEXT("ATTACKING (TBPawn)"));
	intent = TEXT("Attacking!");

	float chanceToHit = abilities->AdjustAttribute(ETargetAttribute::accuracy, accuracy) * 100;
	int dieRoll = 1 + (std::rand() % 100);
	UE_LOG(LogTemp, Display, TEXT("chance to hit %f / die roll %i"), chanceToHit, dieRoll);
	if(chanceToHit >= dieRoll){
		UE_LOG(LogTemp, Display, TEXT("attack hits"));
		float damage = abilities->AdjustAttribute(ETargetAttribute::strength, baseDamage);	
		DealsDamage(target, damage);
	}
	else {
		//TODO: Visualise missing an attack
		UE_LOG(LogTemp, Display, TEXT("attack misses"));
	}
}

bool ATurnBasedPawn::UseSpecialAbility(EAbilityType abilType, ATurnBasedPawn* target){
	int abilityIndex;
	if(abilities->GetAbilityByType(abilType, abilityIndex)){
		UAbility* ability = abilities->GetAbilityArray()[abilityIndex];
		if(ability){
			if((abilities->GetCurrentPower() >= ability->cost) && (ability->cooldownRemain == 0)){
				//UE_LOG(LogTemp, Display, TEXT("Using ability (TBPawn)"));
				intent = ability->name.ToString();
				
				switch(abilType){
					case EAbilityType::buff:
						abilities->AddEffect(ability, true);
						break;
					case EAbilityType::damage:
						abilities->UseDamageAbility(ability, target, this);
						break;
					case EAbilityType::debuff:
						target->abilities->AddEffect(ability, false);
						break;
					case EAbilityType::heal:
						Heal(ability);
						break;
				}

				ability->StartCooldownPeriod();
				abilities->ReduceCurrentPower(ability->cost);

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

bool ATurnBasedPawn::UseAbilityByIndex(int abilInd, ATurnBasedPawn* target){
	if(target){
		UAbility* ability = abilities->GetAbilityArray()[abilInd];
		if(ability){
			if(abilities->GetCurrentPower() >= ability->cost){
				//UE_LOG(LogTemp, Display, TEXT("Using ability (TBPawn)"));

				switch(ability->type){
					case EAbilityType::buff:
						abilities->AddEffect(ability, true);
						break;
					case EAbilityType::damage:
						abilities->UseDamageAbility(ability, target, this);
						break;
					case EAbilityType::debuff:
						target->abilities->AddEffect(ability, false);
						break;
					case EAbilityType::heal:
						Heal(ability);
						break;
				}
				abilities->ReduceCurrentPower(ability->cost);
				return true;
			}
		}
	}
	return false;
}

void ATurnBasedPawn::Defend(){
	//UE_LOG(LogTemp, Display, TEXT("DEFENDING (TBPawn)"));
	intent = TEXT("Defending");

	//TODO: ?
	SetGuarding(true);
}

void ATurnBasedPawn::EndTurn(){
	//decrement any active buff/debuff duration
	abilities->DecrementAllEffectDurations();

	//tell the game mode the turn is done
	if(gameMode){
		UE_LOG(LogTemp, Display, TEXT("Ending turn (TBPawn)"));
		gameMode->EndTurn();
	}
}

float ATurnBasedPawn::GetCurrentHealth(){
	if(health){
		return health->GetCurrentHealth();
	}

	//TODO: something better
	return 0;
}

EHealthState ATurnBasedPawn::GetCurrentState(){
	if(health){
		return health->GetCurrentState();
	}

	//TODO: something better
	return EHealthState::dead;
}

void ATurnBasedPawn::Heal(UAbility* ability){
	if(health){
		health->Heal(ability->damageAmount);
		ability->PlayAbilityVFX(this);
	}
	//TODO ?
}

void ATurnBasedPawn::DecrementEffectDurations(){
	if(abilities){
		abilities->DecrementAllEffectDurations();
	}
	//TODO ?
}

ECombatMood ATurnBasedPawn::GetCurrentMood(){
	if(health){
		return health->GetCurrentMood();
	}

	//TODO: something better
	return ECombatMood::aggro;
}

void ATurnBasedPawn::DealsDamage(AActor* target, float damage){
	auto controller = GetController();
	if(!controller) return;

	ATurnBasedPawn* targetPawn = Cast<ATurnBasedPawn>(target);
	if(targetPawn){
		if(targetPawn->IsGuarding()){
			float damReduce = abilities->AdjustAttribute(ETargetAttribute::defence, guardAmount);
			damage = floor(damage*damReduce);
			targetPawn->SetGuarding(false);
		}
		targetPawn->SetCombatMoodTag();
	}
	
	//TODO: Add damage types
	UGameplayStatics::ApplyDamage(target, damage, controller, this, 
						UDamageType::StaticClass());

}

void ATurnBasedPawn::SetCombatMoodTag(){
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
	UE_LOG(LogTemp, Display, TEXT("Updating tag, dice roll after mods = %i"), dieRoll);   
	
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