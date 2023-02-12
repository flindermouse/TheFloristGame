// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheFloristGameMode.h"
#include "TheFloristCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheFloristGameMode::ATheFloristGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATheFloristGameMode::PawnKilled(APawn* killed){}
