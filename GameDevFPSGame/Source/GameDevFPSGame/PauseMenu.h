// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "PlayerControllerClass.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"


/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PauseToggle(bool
		isPaused); // freezes game

	UFUNCTION(BlueprintCallable)
	void ResumeButton(); // unfreezes game

	UFUNCTION(Blueprintable)
	void QuitGame();

	virtual void NativeConstruct() override; // instantites the buttons
	bool Frozen;
};
