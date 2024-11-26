// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatePattern.h"
#include "UObject/Object.h"
#include "StateManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UStateManager : public UObject
{
	GENERATED_BODY()

private:
	UStatePattern* StateCurrent = nullptr; // currentstate statemanager is in

public:
	void SetState(UStatePattern* setState, UObject* object); // sets statcurrent to new state

	void UpdateState(UObject* object); // updates speed of animation or input
	
};
