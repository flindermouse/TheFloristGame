// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EHealthState : uint8
{
	max UMETA(DisplayName = "Max"),
	healthy UMETA(DisplayName = "Healthy"),
	bloodied UMETA(DisplayName = "Bloodied"),
	dying UMETA(DisplayName = "Dying"),
	dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class ECombatMood : uint8
{
	aggro UMETA(DisplayName = "Aggressive"),
	defence UMETA(DisplayName = "Defensive"),
	scared UMETA(DisplayName = "Scared")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEFLORIST_API UHealthStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const {return currentHealth;}
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetCurrentHealth(float newCurrent) {currentHealth = newCurrent;}
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float healAmount);
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const {return maxHealth;}
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetMaxHealth(float max) {maxHealth = max;}

	//UFUNCTION(BlueprintPure, Category = "Health")
	EHealthState GetCurrentState() const; 
	//UFUNCTION(BlueprintPure, Category = "Mood")
	ECombatMood GetCurrentMood() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float maxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	float currentHealth;

	UFUNCTION()
	void TakeDamage(AActor* damagedAct, float damage, const UDamageType* damageType,
						AController* instigator, AActor* damageCause);
		
};