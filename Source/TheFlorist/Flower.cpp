// Fill out your copyright notice in the Description page of Project Settings.


#include "Flower.h"

#include "Components/StaticMeshComponent.h"

AFlower::AFlower(){
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SetRefMaps();

    type = FName(TEXT("Tulip"));
    colour = FName(TEXT("Red"));
    isActive = false;
    price = UpdatePrice();

    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flower Mesh"));
	RootComponent = mesh;
}

// AFlower::AFlower(FName flType = FName(TEXT("Tulip")), FName flCol = FName(TEXT("Red")), bool isAct = false){
//     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	   PrimaryActorTick.bCanEverTick = false;
//     SetRefMaps();
//
//     type = flType;
//     colour = flCol;
//     isActive = isAct;
//     price = UpdatePrice();
// }

void AFlower::BeginPlay(){
    Super::BeginPlay();
}

void AFlower::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
}

float AFlower::UpdatePrice(){
    float newPrice = 0;

    newPrice += typePrice[type];
    newPrice += colourPrice[colour];

    return newPrice;
}

void AFlower::SetRefMaps(){
    typePrice.Add(FName(TEXT("Rose")), 20.f);
    typePrice.Add(FName(TEXT("Tulip")), 10.f);

    colourPrice.Add(FName(TEXT("Blue")), 5.f);
    colourPrice.Add(FName(TEXT("Red")), 7.5f);
    colourPrice.Add(FName(TEXT("Yellow")), 2.5f);
}