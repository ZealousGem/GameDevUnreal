// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDDisplayClass.generated.h"
// this class handles all the ui
// max when you are working on the ui do it in here,

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API AHUDDisplayClass : public AHUD
{
protected:

	UPROPERTY()
	UUserWidget* CrossHair; // makes the widget display through the hud

	UPROPERTY()
	UUserWidget* CrossDamage; 

	UPROPERTY()
	UUserWidget* Health; 

	UPROPERTY()
	UUserWidget* Ammo;

	UPROPERTY()
	UUserWidget* WeaponType;

public:
	virtual void BeginPlay() override; // overrides default hud class with my amazing hud class

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass; // where you put the cross arm widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass2; // where you put the cross arm widget


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass3; // where you put the cross arm wid

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass4; // where you put the cross arm wid

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass5; // where you put the cross arm wid

	UUserWidget* getCrossDamage() const; // this is useless

	void AmmoDisplay();

	void AmmoHide();
		
	void UpdateAmmo(int32 ammoAmount);

	void HideCorssDamage(bool hitt); // this hides and unhides the crossdamage widget

	bool hit = false; 
	
	void UpdateHealthBar(float HealthPercentage);

	void MainWeapon();

	void SecWeapon();
private:

	GENERATED_BODY()
};
