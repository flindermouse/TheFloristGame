// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheFloristGameMode.h"
#include "GameFramework/GameModeBase.h"

#include "TurnBasedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THEFLORIST_API ATurnBasedGameMode : public ATheFloristGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Player Turn")
	bool GetIsPlayerTurn(){return playerTurn;}
	UFUNCTION(BlueprintCallable, Category = "Player Turn")
	void SetIsPlayerTurn(bool isTurn){playerTurn = isTurn;}
	
	UFUNCTION(BlueprintPure, Category = "End Combat")
	bool GetHasCombatEnded(){return combatEnd;}
	UFUNCTION(BlueprintCallable, Category = "End Combat")
	void SetHasCombatEnded(bool isEnd){combatEnd = isEnd;}

	UFUNCTION(BlueprintPure, Category = "End Combat")
	bool GetHasPlayerWon(){return playerWin;}
	UFUNCTION(BlueprintCallable, Category = "End Combat")
	void SetHasPlayerWon(bool hasWon){playerWin = hasWon;}

	UFUNCTION()
	void EndTurn();

	UFUNCTION()
	void EndCombat(bool playerWon);

	void PawnKilled(APawn* dead) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player Turn")
	bool playerTurn;

	UPROPERTY(VisibleAnywhere, Category = "End Combat")
	bool combatEnd = false;
	UPROPERTY(VisibleAnywhere, Category = "End Combat")
	bool playerWin = false;

	//void SpawnCombatants();

};
