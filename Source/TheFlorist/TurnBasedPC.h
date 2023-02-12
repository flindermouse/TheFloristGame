// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TurnBasedPC.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API ATurnBasedPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	float restartDelay = 3;
	FTimerHandle restartTimer;


};
