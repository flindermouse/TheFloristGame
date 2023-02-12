// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ability.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Enemy.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class THEFLORIST_API UEnemy : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float strength = 1.f; //multiplies baseDamage on TBP

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float endurance = 1.f; //multiplies maxHealth on TBP

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float experience = 1.f; //multiplies maxPower on TBP

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAbility*> abilities;

	//TODO:
	// add anims
	// add sounds


	
};
