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
