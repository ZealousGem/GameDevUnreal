// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDDisplayClass.generated.h"



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
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass; // where you put the cross arm widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass2; // where you put the cross arm widget

	UUserWidget* getCrossDamage() const;
	
		
	

	void HideCorssDamage(bool hitt);

	bool hit = false;
	
private:
	GENERATED_BODY()
};
