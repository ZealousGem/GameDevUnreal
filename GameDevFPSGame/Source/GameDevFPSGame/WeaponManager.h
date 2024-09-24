// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "HUDDisplayClass.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEDEVFPSGAME_API UWeaponManager : public UActorComponent
{
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Sets default values for this component's properties
	UWeaponManager();

	void HandleSwitch(); // switches the primary and secondary weapon

	void Tracing(); // creates the line trace and makes the gun go "pew" "pew"

	void HandleFire(); // activates the tracing method through the keybinding

	void Released(); // will stop ammo counter to decreases




private:
	
	AMyCharacter* PlayerCharacter = nullptr; // creates a mycharacter object

	AHUDDisplayClass* display =nullptr; // creates a hud object

	bool fireinframe = false; // use detect a shot has been made by a weapon

	bool spint = false;
	FTimerHandle TimerHandle_HideWidget; // a timer used for the crossdamage widget which will stay active until 0.5 seconds
	void HidedamageWidget();
	GENERATED_BODY()


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
