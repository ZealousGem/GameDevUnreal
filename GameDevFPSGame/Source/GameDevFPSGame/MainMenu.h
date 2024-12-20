﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

    UFUNCTION()
    void StartGameButton();

    UFUNCTION()
    void QuitGameButton();

    virtual void NativeConstruct() override;

};
