// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "GameFramework/Actor.h"
#include "UObject/NameTypes.h"

#include "Flower.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API AFlower : public AActor
{
	GENERATED_BODY()

public:
	AFlower();
	//AFlower(FName flType, FName, bool isAct);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	bool GetActive() {return isActive;}
	void SetActive(bool isAct) {isActive = isAct;}

	// changing meshes is easier within blueprints, just update FNames
	UFUNCTION(BlueprintPure, Category = "Flower Type")
	FName GetType() {return type;}
	UFUNCTION(BlueprintCallable, Category = "Flower Type")
	void SetType(FName newType) {type = newType;}
	UFUNCTION(BlueprintPure, Category = "Flower Colour")
	FName GetColour() {return colour;}
	UFUNCTION(BlueprintCallable, Category = "Flower Colour")
	void SetColour(FName newCol) {colour = newCol;}

	//
	float UpdatePrice();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Activate")
	bool isActive;
	UPROPERTY(VisibleAnywhere, Category = "Price")
	float price;
	UPROPERTY(VisibleAnywhere, Category = "Customisation")
	FName type;
	UPROPERTY(VisibleAnywhere, Category = "Customisation")
	FName colour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;	

	// references TODO: read these from somewhere else
	TMap<FName, float> typePrice;
	TMap<FName, float> colourPrice;
	void SetRefMaps();

};
