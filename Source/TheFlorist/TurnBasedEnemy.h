// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurnBasedPawn.h"

#include "TurnBasedEnemy.generated.h"

UENUM(BlueprintType)
enum class ECombatMood : uint8
{
	aggro UMETA(DisplayName = "Aggressive"),
	defence UMETA(DisplayName = "Defensive"),
	scared UMETA(DisplayName = "Scared")
};

/**
 * 
 */
UCLASS()
class THEFLORIST_API ATurnBasedEnemy : public ATurnBasedPawn, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ATurnBasedEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//Mood
	UFUNCTION(BlueprintPure, Category = "Mood")
	ECombatMood GetCurrentMood();
	UFUNCTION(BlueprintCallable, Category = "Mood")
	void SetCombatMoodTag();

	//Gameplay Tags
	UFUNCTION(BlueprintPure, Category = "GameplayTags")
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = gameplayTags; return; }

	// combat
	UFUNCTION(BlueprintCallable, Category = "Combat Actions")
	bool UseSpecialAbility(enum EAbilityType abilType, ATurnBasedPawn* target = nullptr);

	virtual void Attack(AActor* target) override;

	// anim
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayIdle();

private:
	USkeletalMeshComponent* skelly;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer gameplayTags;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEnemy* enemyType;

};
