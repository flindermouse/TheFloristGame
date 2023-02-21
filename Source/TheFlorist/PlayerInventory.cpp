// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

#include "Item.h"

void UPlayerInventory::AddItem(UItem* newItem){
    int count = 1;
    if(items.Contains(newItem)){
        count += *items.Find(newItem);
    }
    
    items.Add(newItem, count);
}

void UPlayerInventory::RemoveItem(UItem* oldItem){
    if(*items.Find(oldItem) > 1){
        int count = *items.Find(oldItem) - 1;
        items.Add(oldItem, count);
    }
    else{
        items.Remove(oldItem);
    }
}

float UPlayerInventory::RestoreMeter(UItem* itemUsed, float meterMax){

    if(!itemUsed) return 0.f;
    
    return (meterMax / 100) * itemUsed->percentEffective;
}

float UPlayerInventory::IncreaseStat(UItem* itemUsed){
    if(!itemUsed) return 1.f;

    return (itemUsed->percentEffective / 100) + 1;
}