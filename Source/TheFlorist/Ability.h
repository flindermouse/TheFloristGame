// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Ability.generated.h"

class UNiagaraSystem;

/**
 * 
 */
UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	damage UMETA(DisplayName = "Damage"),
	debuff UMETA(DisplayName = "Debuff"),
	buff UMETA(DisplayName = "Buff"),
	heal UMETA(DisplayName = "Heal")
};

UENUM(BlueprintType)
enum class EDamageType : uint8{
	none UMETA(DisplayName = "None"),
	base UMETA(DiplayName = "Base"),
	fire UMETA(DisplayName = "Fire"),
	poison UMETA(DisplayName = "Poison")
};

UENUM(BlueprintType)
enum class ETargetAttribute : uint8{
	none UMETA(DisplayName = "None"),
	strength UMETA(DisplayName = "Strength"),
	endurance UMETA(DisplayName = "Endurance"),
	stamina UMETA(DisplayName = "Stamina"),
	accuracy UMETA(DisplayName = "Accuracy"),
	defence UMETA(DisplayName = "Defence")
};

UCLASS(BlueprintType)
class THEFLORIST_API UAbility : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityGeneral")
	FName name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityGeneral")
	EAbilityType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityGeneral")
	float cost; //how much power used
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityGeneral")
	UNiagaraSystem* abilityVFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityCooldown")
	int cooldownTotal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityCooldown")
	int cooldownRemain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityDamage")
	EDamageType damageType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilityDamage")
	float damageAmount; //also use for heal amount

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySpecial")
	int durationTotal; //how many turns the effect lasts
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySpecial")
	int durationRemain; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySpecial")
	float magnitude; //how strong is the effect (used to multiply or divide stats for duration)	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AbilitySpecial")
	ETargetAttribute attribute;

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void StartCooldownPeriod();
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void DecrementCooldownRemain();
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void ResetCooldownRemain();

	UFUNCTION(BlueprintCallable, Category = "Duration")
	void StartDuration();
	UFUNCTION(BlueprintCallable, Category = "Duration")
	void DecrementDurationRemain();

	UFUNCTION()
	void PlayAbilityVFX(AActor* target);
};
