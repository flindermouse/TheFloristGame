// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"

#include "PlayerInventory.generated.h"

class UItem;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEFLORIST_API UPlayerInventory : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Items")
	void AddItem(UItem* newItem);
	UFUNCTION(BlueprintCallable, Category = "Items")
	void RemoveItem(UItem* oldItem);

	UFUNCTION(BlueprintPure, Category = "Items")
	TMap<UItem*, int> GetItemMap() const { return items; }
	UFUNCTION(BlueprintCallable, Category = "Items")
	void SetItemMap(TMap<UItem*, int> newItems) {items = newItems;}

	UFUNCTION(BlueprintCallable, Category = "Use Item")
	float RestoreMeter(UItem* itemUsed, float meterMax);
	UFUNCTION(BlueprintCallable, Category = "Use Item")
	float IncreaseStat(UItem* itemUsed);

private:
	UPROPERTY(VisibleAnywhere, Category = "Items")
	TMap<UItem*, int> items;

};
