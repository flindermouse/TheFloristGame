// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "GameFramework/Actor.h"

#include "Bouquet.generated.h"

class AFlower;

UCLASS()
class THEFLORIST_API ABouquet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouquet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Add flower to bouquet
	UFUNCTION(BlueprintCallable, Category = "AddRemove")
	void AddFlower();
	// Remove flower from bouquet
	UFUNCTION(BlueprintCallable, Category = "AddRemove")
	void RemoveFlower(int flowerInd);

	//
	UFUNCTION(BlueprintCallable, Category = "Activate")
	void SetActiveFlower();
	UFUNCTION(BlueprintCallable, Category = "Activate")
	void SetActiveFlowerIndex(int newInd) {activeFlowerInd = newInd;}
	UFUNCTION(BlueprintPure, Category = "Activate")
	int GetActiveFlowerIndex() {return activeFlowerInd;}

	UFUNCTION(BlueprintPure, Category = "Bouquet")
	TArray<AFlower*> GetBouquet() {return flowers;}
	//
	UFUNCTION(BlueprintCallable, Category = "Bouquet Price")
	void UpdatePrice();
	UFUNCTION(BlueprintPure, Category = "Bouquet Price")
	float GetPrice() {return totalPrice;}

private:
	UPROPERTY(VisibleDefaultsOnly)
	TArray<AFlower*> flowers;
	UPROPERTY()
	int activeFlowerInd;
	UPROPERTY(VisibleDefaultsOnly)
	float totalPrice;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<AFlower> flowerClass;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* flowerSpawn;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* cam;
};
