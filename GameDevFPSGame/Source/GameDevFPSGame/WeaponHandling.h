// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "WeaponHandling.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UWeaponHandling : public UObject
{
	GENERATED_BODY()
public:
	UWeaponHandling();

	void Activate(AMyCharacter* isPlayerCharacter, AHUDDisplayClass* DisplayHUD);

	void Tracing();  // creates the line trace and makes the gun go "pew" "pew"
	void HandleFire();
	void Released();
    void HideWidget();
	void SwitchWeapon();
	
private:

     AMyCharacter* PlayerCharacter;

	AHUDDisplayClass* display;

	FTimerHandle TimerHandle_HideWidget;

	bool FireInFrame = false; 
	


	// Weapon Functions

};
