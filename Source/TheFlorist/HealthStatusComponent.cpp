// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthStatusComponent.h"

#include "TheFloristGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthStatusComponent::UHealthStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	//start at full health
	currentHealth = maxHealth;
	
	//bind TakeDamage to the pawns take any damage event
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthStatusComponent::TakeDamage);
}


// Called every frame
void UHealthStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UHealthStatusComponent::GetHealthPercent() const{
	return currentHealth / maxHealth;
}

void UHealthStatusComponent::Heal(float healAmount){
	currentHealth += healAmount;
	if(currentHealth > maxHealth){
		currentHealth = maxHealth;
	}
}

EHealthState UHealthStatusComponent::GetCurrentState() const{
	if(currentHealth == maxHealth){
		return EHealthState::max;
	}
	else if(currentHealth > ((maxHealth/100)*50)){
		return EHealthState::healthy;
	}
	else if(currentHealth > ((maxHealth/100)*20)){
		return EHealthState::bloodied;
	}
	else if(currentHealth <= 0){
		return EHealthState::dead;
	}
	else{
		return EHealthState::dying;
	}
}

void UHealthStatusComponent::TakeDamage(AActor* damagedAct, float damage, const UDamageType* damageType,
								AController* instigator, AActor* damageCause){
	if(damage <= 0.f) return;

	currentHealth -= damage;
	UE_LOG(LogTemp, Display, TEXT("%f damage taken!"), damage);			

	if(GetCurrentState() == EHealthState::dead){
		UE_LOG(LogTemp, Warning, TEXT("Target killed"));

		//tell the game mode someone is dead
		ATheFloristGameMode* gameMode = GetWorld()->GetAuthGameMode<ATheFloristGameMode>();
		if(!gameMode) return;

		APawn* deadPawn = Cast<APawn>(GetOwner());
		if(!deadPawn) return;

		gameMode->PawnKilled(deadPawn);

		if(!deadPawn->GetController()->IsPlayerController()){ //only destroy if enemy
			// get ready for destruction + turn off collisions
			deadPawn->DetachFromControllerPendingDestroy(); 
			deadPawn->Destroy();
			UE_LOG(LogTemp, Warning, TEXT("Pawn destroyed (HSComp)"))
		}
		else{
			UE_LOG(LogTemp, Warning, TEXT("Player defeated (HSComp)"));
		}
	}			
}
