﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "LeaderBoardManager.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "GameFramework/HUD.h"
#include "HUDDisplayClass.generated.h"
// this class handles all the ui


/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API AHUDDisplayClass : public AHUD
{

	GENERATED_BODY()
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

	UPROPERTY()
	UUserWidget* Death;

	UPROPERTY()
	UUserWidget* LeaderBoard;

	UPROPERTY()
	UUserWidget* Timer;

	UPROPERTY()
	UUserWidget* PauseMenu;

	UPROPERTY()
	UUserWidget* PickUp;

	UPROPERTY()
	ULeaderBoardManager* LeaderBoardManager = nullptr;

	UPROPERTY()
	UPauseMenu* PauseFunc = nullptr;

	UPROPERTY()
	UUserWidget* GameOverMenu;

	UPROPERTY()
	UGameOverMenu* OverPauseFunc = nullptr;

public:

	virtual void BeginPlay() override; // overrides default hud class with my this class

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass; // where you put the cross arm widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass2; // where you put the cross arm widget


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass3; // For health widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass4; //For ammo widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass5; // For weapon widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass6; // For weapon widget

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass7; // For leaderboard

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass8; // For timer

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass9; // For pause menu

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass10; // For gameover menu

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> mywidgetClass11; // For pickupUI

	UUserWidget* getCrossDamage() const;

	int32 Minutes = 3;

	int32 Seconds = 0;

	void Counter();

	void AmmoDisplay(); // displays ammo if shotgun is equipped

	void AmmoHide(); // hides ammo widget when not equipped

	void UpdateAmmo(int32 ammoAmount);

	void HideCorssDamage(bool hitt); // this hides and unhides the crossdamage widget

	bool hit = false;  // stops ammo counter from going down more than once

	void UpdateHealthBar(float HealthPercentage); // handles updates the health bar widget bar

	void MainWeapon(); // widget ui text changes to primary weapon

	void SecWeapon(); // widget ui text changes to secondary weapon

	void displayDeath(bool hitt);

	void TimerDeath();

	void UpdateLeaderBoard();
	void ShowLeaderBoard();

	void HideLeaderBoard();

	void UpdatePlayerCount();

	void UpdateBotCount(FString Bot);

	void PauseGame();

	void HidePuaseMenu();

	void UnHidePasueMenu();

	void GameOver();

	void HideGameOverMenu();

	void UnHideGameOverMenu();

	void AmmoDisplay(bool show, FString pick);

	void AmmoHidden();

private:

		bool isPaused;




};
