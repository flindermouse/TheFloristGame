// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "AbilityComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEFLORIST_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Capacity")
	int GetMaxCapacity() const {return maxCapacity;}
	UFUNCTION(BlueprintCallable, Category = "Capacity")
	void SetMaxCapacity(int max) {maxCapacity = max;}
	UFUNCTION(BlueprintCallable, Category = "Capacity")
	void IncrementMaxCapacity() {maxCapacity += 1;}
	UFUNCTION(BlueprintPure, Category = "Capacity")
	int GetCurrentCapacity() {return abilities.Num();}

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetMaxPower() const {return maxPower;}
	UFUNCTION(BlueprintCallable, Category = "Power")
	void SetMaxPower(float max) {maxPower = max;}

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower() const {return currentPower;}
	UFUNCTION(BlueprintCallable, Category = "Power")
	void SetCurrentPower(float newCurrent) {currentPower = newCurrent;}
	UFUNCTION(BlueprintCallable, Category = "Power")
	void ReduceCurrentPower(float reduce) {currentPower -= reduce;}
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerPercent() const;

	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerRegenRate() const {return powerRegenRate;}
	UFUNCTION(BlueprintCallable, Category = "Power")
	void SetPowerRegenRate(float rate) {powerRegenRate = rate;}
	UFUNCTION(BlueprintCallable, Category = "Power")
	void RegeneratePower(bool useDefaultRate = true, float regenRate = 0);

	UFUNCTION(BlueprintCallable, Category = "Use Ability")
	bool GetAbilityByType(EAbilityType targetType, int &outIndex);
	UFUNCTION(BlueprintCallable, Category = "Use Ability")
	bool GetAbilityByName(FName abilName, int &outIndex);
	UFUNCTION(BlueprintCallable, Category = "Use Ability")
	void DecrementAllCooldowns();
	UFUNCTION(BlueprintCallable, Category = "Use Ability")
	void ResetCooldown(int abilInd);

	UFUNCTION(BlueprintPure, Category = "Abilities")
	TArray<UAbility*> GetAbilityArray() const {return abilities;}
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SetAbilityArray(TArray<UAbility*> newAbils) {abilities = newAbils;}
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void AddAbility(UAbility* newAbility);
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RemoveAbility(UAbility* oldAbility);
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool HasAbilities() {return !abilities.IsEmpty(); }

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void AddEffect(UAbility* ability, bool isBuff);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void RemoveEffect(ETargetAttribute attribute, bool isBuff);
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void CheckAndRemoveLapsedEffects();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	void DecrementAllEffectDurations();
	UFUNCTION(BlueprintCallable, Category = "Effects")
	float AdjustAttribute(ETargetAttribute attribute, float base);
	UFUNCTION(BlueprintPure, Category = "Effects")
	TMap<ETargetAttribute, UAbility*> GetBuffs() const {return buffs;}
	UFUNCTION(BlueprintPure, Category = "Effects")
	TMap<ETargetAttribute, UAbility*> GetDebuffs() const {return debuffs;}

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void UseDamageAbility(UAbility* ability, AActor* target, AActor* instigator);

private: 

	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	TArray<UAbility*> abilities;

	UPROPERTY(VisibleAnywhere, Category = "Capacity")
	int maxCapacity = 1;

	UPROPERTY(VisibleAnywhere, Category = "Power")
	float maxPower = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float currentPower;
	UPROPERTY(VisibleAnywhere, Category = "Power")
	float powerRegenRate = 10.f;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TMap<ETargetAttribute, UAbility*> buffs;
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TMap<ETargetAttribute, UAbility*> debuffs;
		
};
