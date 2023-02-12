// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheFloristGameMode.generated.h"

UCLASS(minimalapi)
class ATheFloristGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheFloristGameMode();

	virtual void PawnKilled(APawn* killed);
};



