// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Item.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8{
	cutFlower UMETA(DisplayName = "Flower"),
	equip UMETA(DisplayName = "Gardening Equipment"),
	consumable UMETA(DisplayName = "Consumable")
};

UCLASS(BlueprintType)
class THEFLORIST_API UItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FName name;	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	EItemType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
	FString description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Use")
	float percentEffective;
};
