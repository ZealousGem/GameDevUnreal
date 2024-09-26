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
	void HandleFire(); // handles firing spray
	void Released(); // will set inframe to false for weapon to fire agian
    void HideWidget(); // hides the damage ui widget
	void SwitchWeapon(); // switches between the primary and secondary weapon
	
private:

     AMyCharacter* PlayerCharacter; // empty character class to be used to instatiate object through activate method

	AHUDDisplayClass* display; // empty hud class to be used to instatiate object through activate method

	FTimerHandle TimerHandle_HideWidget; // this will be the amount of time the damage widget will display

	bool FireInFrame = false; 
	


	// Weapon Functions

};
