// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Pawn.h"

#include "TurnBasedPawn.generated.h"

UCLASS()
class THEFLORIST_API ATurnBasedPawn : public APawn, public IGameplayTagAssetInterface
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
	void Attack(AActor* target);
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	bool UseSpecialAbility(enum EAbilityType abilType, ATurnBasedPawn* target = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	bool UseAbilityByIndex(int abilInd, ATurnBasedPawn* target = nullptr);
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

	//Health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth();
	UFUNCTION(BlueprintPure, Category = "Health")
	EHealthState GetCurrentState();

	//heal
	UFUNCTION(BlueprintCallable, Category = "Healing")
	void Heal(UAbility* ability);

	//ongoing effects
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void DecrementEffectDurations();

	//Mood
	UFUNCTION(BlueprintPure, Category = "Mood")
	ECombatMood GetCurrentMood();
	UFUNCTION(BlueprintCallable, Category = "Mood")
	void SetCombatMoodTag();

	//Intent
	UFUNCTION(BlueprintPure, Category = "Intent")
	FString GetIntent() const {return intent;}
	UFUNCTION(BlueprintCallable, Category = "Intent")
	void SetIntent(FString newIn) {intent = newIn;}

	//Gameplay Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer gameplayTags;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = gameplayTags; return; }

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

	UFUNCTION()
	void DealsDamage(AActor* target, float damage);
};
