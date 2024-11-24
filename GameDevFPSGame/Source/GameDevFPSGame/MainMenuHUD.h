// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UUserWidget* Title; // makes the widget display through the hud

	UPROPERTY()
	UUserWidget* Menu;
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass; // where you put the cross arm widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass2;
};
