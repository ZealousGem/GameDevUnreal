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
		isPaused);

	UFUNCTION(BlueprintCallable)
	void ResumeButton();

	virtual void NativeConstruct() override;
	bool Frozen;
};
