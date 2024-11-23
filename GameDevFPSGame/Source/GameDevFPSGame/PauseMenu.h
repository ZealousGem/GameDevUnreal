// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
	void ResumeGame();


	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
	void QuitToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Pause Menu")
	void RestartLevel();

};
