// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "AmmoPickUp.h"
#include "WeaponpPickUp.h"
#include "WeaponHandling.h"
#include "MyCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UGameManager* gameManager;
};
