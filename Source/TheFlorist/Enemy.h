// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float strength = 1.f; //multiplies baseDamage on TBP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float endurance = 1.f; //multiplies maxHealth on TBP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	float experience = 1.f; //multiplies maxPower on TBP
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	bool isBoss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	USkeletalMesh* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimationAsset* idle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimationAsset* attack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimationAsset* hit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimationAsset* cast;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UAnimationAsset* guard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<class UAbility*> abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rewards")
	TArray<class UItem*> rewards;

	//TODO:
	// add anims
	// add sounds


	
};
