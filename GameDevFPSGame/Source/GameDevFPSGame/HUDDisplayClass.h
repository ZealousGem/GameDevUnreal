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
	UUserWidget* CrossDamage; // makes the widget display through the hud

public:
	virtual void BeginPlay() override; // overrides default hud class with my amazing hud class


	
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass; // where you put the cross arm widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass2; // where you put the cross arm widget

	UUserWidget* getCrossDamage() const; // this is useless
	
		
	

	void HideCorssDamage(bool hitt); // this hides and unhides the crossdamage widget

	bool hit = false; // useless code, fuck i am messy when it comes to coding
	
private:

	

	GENERATED_BODY()
};
