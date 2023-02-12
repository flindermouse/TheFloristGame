// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabs.h"

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabs::UGrabs()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabs::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabs::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* handle = GetPhysicsHandle();
	if(!handle) return;

	if(!handle->GetGrabbedComponent()){
		//UE_LOG(LogTemp, Display, TEXT("not holding anything"));
		return;
	}

	FVector targetLoc, targetDir;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(targetLoc, targetDir);
	FVector currentLoc;
	FRotator currentRot; 
	handle->GetTargetLocationAndRotation(currentLoc, currentRot);//handle->GetGrabbedComponent()->GetComponentLocation();
	targetLoc.X += currentLoc.X;
	targetLoc.Y = currentLoc.Y; 
	targetLoc.Z += currentLoc.Z;

	UE_LOG(LogTemp, Display, TEXT("current location x %f y %f z %f"), currentLoc.X, currentLoc.Y, currentLoc.Z);
	UE_LOG(LogTemp, Display, TEXT("target location x %f y %f z %f"), targetLoc.X, targetLoc.Y, targetLoc.Z);

	handle->SetTargetLocationAndRotation(targetLoc, currentRot); //handle->GetGrabbedComponent()->GetComponentRotation());

	//currentLoc = handle->GetGrabbedComponent()->GetComponentLocation();
	handle->GetTargetLocationAndRotation(currentLoc, currentRot);
	UE_LOG(LogTemp, Display, TEXT("current location x %f y %f z %f"), currentLoc.X, currentLoc.Y, currentLoc.Z);
}

void UGrabs::Grab(){
	UPhysicsHandleComponent* handle = GetPhysicsHandle();
	if(!handle) return;

	FHitResult hitRes;
	bool hasHit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, hitRes);
	if(hasHit){
		UPrimitiveComponent* hitComp = hitRes.GetComponent();
		UE_LOG(LogTemp, Display, TEXT("grabbin %s"), *hitComp->GetName());
		hitComp->WakeAllRigidBodies();
		handle->GrabComponentAtLocationWithRotation(hitComp, NAME_None, hitRes.ImpactPoint, GetComponentRotation());
		//hitRes.GetComponent()->GetComponentRotation());
	}
	else{
		UE_LOG(LogTemp, Display, TEXT("nothing to grab"));
	}
}

void UGrabs::Release(){
	UPhysicsHandleComponent* handle = GetPhysicsHandle();
	if(!handle) return;

	if(handle->GetGrabbedComponent()){
		UE_LOG(LogTemp, Display, TEXT("lettin go"));
		handle->GetGrabbedComponent()->WakeAllRigidBodies();
		handle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabs::GetPhysicsHandle() const{
	UPhysicsHandleComponent* handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(!handle){
		UE_LOG(LogTemp, Error, TEXT("no physics handle found"));
	}

	return handle;
}