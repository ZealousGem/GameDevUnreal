// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UGameOverMenu : public UUserWidget
{

protected:

    UFUNCTION()
    void RestartButton();

    // Called when the "Quit" button is clicked
    UFUNCTION()
    void QuitButton();

    // Called when the "Main Menu" button is clicked
    UFUNCTION()
    void MainMenuButton();

	//bool Frozen;

	virtual void NativeConstruct() override;

public:

    bool Frozen;
	void ToggleEndMenu(bool isPaused);

	GENERATED_BODY()
};
