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
}

// Called every frame
void ATurnBasedPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayIdle();
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

	if(hasGuard){ //defending only lasts 1 turn
		SetGuarding(false);
	}
}

void ATurnBasedPawn::Attack(AActor* target){
	//UE_LOG(LogTemp, Display, TEXT("ATTACKING (TBPawn)"));
	intent = TEXT("Attacking!");

	float chanceToHit = abilities->AdjustAttribute(ETargetAttribute::accuracy, accuracy) * 100;
	int dieRoll = 1 + (std::rand() % 100);
	//UE_LOG(LogTemp, Display, TEXT("chance to hit %f / die roll %i"), chanceToHit, dieRoll);
	if(chanceToHit >= dieRoll){
		//UE_LOG(LogTemp, Display, TEXT("attack hits"));
		float damage = abilities->AdjustAttribute(ETargetAttribute::strength, baseDamage);	
		DealsDamage(target, damage);
	}
	else {
		//UE_LOG(LogTemp, Display, TEXT("attack misses"));
		hasMissed = true;
	}
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
						UseHealingAbility(ability);
						break;
				}
				abilities->ReduceCurrentPower(ability->cost);
				return true;
			}
		}
	}
	return false;
}

void ATurnBasedPawn::UseHealingAbility(UAbility* ability){
	if(ability){
		if(health){
			health->Heal(ability->damageAmount);
			ability->PlayAbilityVFX(this);
		}
	}
}

void ATurnBasedPawn::Defend(){
	//UE_LOG(LogTemp, Display, TEXT("DEFENDING (TBPawn)"));
	intent = TEXT("Defending");

	SetGuarding(true);
}

void ATurnBasedPawn::EndTurn(){
	//reset missed bool
	hasMissed = false;

	//decrement any active buff/debuff duration
	abilities->DecrementAllEffectDurations();

	//tell the game mode the turn is done
	if(gameMode){
		//UE_LOG(LogTemp, Display, TEXT("Ending turn (TBPawn)"));
		gameMode->EndTurn();
	}
}

void ATurnBasedPawn::DecrementEffectDurations(){
	if(abilities){
		abilities->DecrementAllEffectDurations();
	}
}

void ATurnBasedPawn::PlayIdle(){
	USkeletalMeshComponent* skelly = Cast<USkeletalMeshComponent>(GetRootComponent());

	if(!skelly) return;
	if(skelly->IsPlaying()) return;
	skelly->PlayAnimation(idle, true);
}

void ATurnBasedPawn::DealsDamage(AActor* target, float damage){
	auto controller = GetController();
	if(!controller) return;
	if(!target) return;

	ATurnBasedPawn* targetPawn = Cast<ATurnBasedPawn>(target);
	if(targetPawn){
		if(targetPawn->IsGuarding()){
			float damReduce = abilities->AdjustAttribute(ETargetAttribute::defence, guardAmount);
			damage = floor(damage*damReduce);
			targetPawn->SetGuarding(false);
		}
	}
	
	//TODO: Add damage types
	UGameplayStatics::ApplyDamage(target, damage, controller, this, 
						UDamageType::StaticClass());

}

