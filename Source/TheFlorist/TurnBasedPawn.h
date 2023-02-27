// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Pawn.h"

#include "TurnBasedPawn.generated.h"

UCLASS()
class THEFLORIST_API ATurnBasedPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurnBasedPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Combat actions
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	void StartTurn();
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	virtual void Attack(AActor* target);
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	bool UseAbilityByIndex(int abilInd, ATurnBasedPawn* target = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	void UseHealingAbility(UAbility* ability);
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	void Defend();
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	void EndTurn();

	UFUNCTION(BlueprintPure, Category = "Defence")
	bool IsGuarding() const {return hasGuard;}
	UFUNCTION(BlueprintCallable, Category = "Defence")
	void SetGuarding(bool guard) {hasGuard = guard;}
	UFUNCTION(BlueprintPure, Category = "Defence")
	float GetGuardAmount() const {return guardAmount;}
	UFUNCTION(BlueprintCallable, Category = "Defence")
	void SetGuardAmount(float newGuard) {guardAmount = newGuard;}

	UFUNCTION(BlueprintPure, Category = "Damage")
	float GetBaseDamage() const {return baseDamage;}
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetBaseDamage(float damage) {baseDamage = damage;}

	UFUNCTION(BlueprintPure, Category = "Accuracy")
	float GetAccuracy() const {return accuracy;}
	UFUNCTION(BlueprintCallable, Category = "Accuracy")
	void SetAccuracy(float newAcc) {accuracy = newAcc;}

	//ongoing effects
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void DecrementEffectDurations();

	//Intent
	UFUNCTION(BlueprintPure, Category = "Intent")
	FString GetIntent() const {return intent;}
	UFUNCTION(BlueprintCallable, Category = "Intent")
	void SetIntent(FString newIn) {intent = newIn;}

	//health + abilities
	class UHealthStatusComponent* GetHealthComponent(){return health;}
	class UAbilityComponent* GetAbilityComponent(){return abilities;}

	//damage 
	virtual void DealsDamage(AActor* target, float damage);

private:
	class ATurnBasedGameMode* gameMode;
	class UHealthStatusComponent* health;
	class UAbilityComponent* abilities;

	UPROPERTY(VisibleAnywhere, Category = "Damage")
	float baseDamage = 15;
	UPROPERTY(VisibleAnywhere, Category = "Defence")
	bool hasGuard = false;
	UPROPERTY(VisibleAnywhere, Category = "Defence")
	float guardAmount = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "Accuracy")
	float accuracy = 0.95f;

	UPROPERTY(VisibleAnywhere, Category = "Intent")
	FString intent = TEXT("");
};
