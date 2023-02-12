// Fill out your copyright notice in the Description page of Project Settings.


#include "Bouquet.h"

#include "Flower.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABouquet::ABouquet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flowerSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Flower Spawn Point"));
	RootComponent = flowerSpawn;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(flowerSpawn);

    cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    cam->SetupAttachment(springArm);

	totalPrice = 0;
}

// Called when the game starts or when spawned
void ABouquet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABouquet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//
void ABouquet::AddFlower(){
	// spawn a new flower
	if(!flowerSpawn){
		UE_LOG(LogTemp, Error, TEXT("No spawn point found"));
	}
	else{
		//AFlower* flower = GetWorld()->SpawnActor<AFlower>(flowerClass, flowerSpawn->GetComponentLocation(),
		//					flowerSpawn->GetComponentRotation());
		AFlower* flower = GetWorld()->SpawnActor<AFlower>(AFlower::StaticClass(), flowerSpawn->GetComponentLocation(),
							flowerSpawn->GetComponentRotation());
		if(!flower){
			UE_LOG(LogTemp, Error, TEXT("Flower not created"));
		}
		else{
			UE_LOG(LogTemp, Display, TEXT("Flower created"));

			flower->SetOwner(this);

			// add it to array
			flowers.Add(flower);

			// set it as the active flower
			activeFlowerInd = (flowers.Num() - 1);
			SetActiveFlower();

			//update the current total bouquet price
			UpdatePrice();

			//TODO: reposition flowers?
		}
	}
}

void ABouquet::RemoveFlower(int flowInd){
	// remove from array
	AFlower* remove = flowers[flowInd];
	flowers.RemoveAt(flowInd);

	// get new active index
	//(next lowest index, or highest index if current is 0)
	if(flowInd == 0){
		activeFlowerInd = (flowers.Num() - 1);
	}
	else{
		activeFlowerInd--;
	}

	// destroy flower
	if(remove){
		remove->Destroy();
	}

	// set new active flower
	SetActiveFlower();

	//TODO: reposition flowers?
}

//
void ABouquet::SetActiveFlower(){
	bool isAct;
	for(int i = 0; i < flowers.Num(); i++){
		if(i == activeFlowerInd){
			isAct = true;
		}
		else{
			isAct = false;
		}

		if(flowers[activeFlowerInd]){ //TODO: Handle this better
			flowers[activeFlowerInd]->SetActive(isAct);
		}
	}
}

//
void ABouquet::UpdatePrice(){
	totalPrice = 0;

	for(AFlower* flower : flowers){
		if(!flower) return; //TODO: Handle this better

		totalPrice += flower->UpdatePrice();
	}
}
