﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDisplayClass.h"

#include "LeaderBoardManager.h"
#include "PlayerControllerClass.h"
#include "Components/ProgressBar.h"  // For UProgressBar
#include "Components/TextBlock.h"    // For UTextBlock
#include "Components/VerticalBox.h"
#include "GameFrameWork/PlayerController.h"

#include "GameOverMenu.h"



void AHUDDisplayClass::BeginPlay()
{
	Super::BeginPlay();

	

	FTimerHandle TimerHandle;
GetWorldTimerManager().SetTimer(TimerHandle, this, &AHUDDisplayClass::Counter, 1.f, true, 0.0);
isPaused = false;
	
	if(mywidgetClass)
	{
		// allows unreal to access the class through blueprints 
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass);
		CrossDamage = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass2);
		Health = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass3);
		Ammo = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass4);
		WeaponType = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass5);
		Death = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass6);
		LeaderBoard = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass7);
		Timer = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass8);
		PauseMenu = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass9);
		GameOverMenu= CreateWidget<UUserWidget>(GetWorld(), mywidgetClass10);
		PickUp= CreateWidget<UUserWidget>(GetWorld(), mywidgetClass11);

		

		if(CrossHair) // checks if widget has been added
		{
		CrossHair->AddToViewport(2);	// sets crosshair under the cross damage layer
		}
       
		if(mywidgetClass2) // checks if widget has been added
		{
			CrossDamage->AddToViewport(1); // sets the wdiget layer above the crosshair
			CrossDamage->SetVisibility(ESlateVisibility::Hidden); // hides the widget once the game starts
			 // when the program starts it will amke the widget hidden
		}
		if (Health) // checks if widget has been added
		{
			Health->AddToViewport(3);	// sets crosshair under the cross damage layer
		}

		if(Ammo) // checks if widget has been added
		{
			Ammo->AddToViewport(4);
			Ammo->SetVisibility(ESlateVisibility::Hidden);
		}

		if(WeaponType) // checks if widget has been added
		{
			WeaponType->AddToViewport(5);
			
		
		}

		if(Death)
		{
			Death->AddToViewport(6);
			Death->SetVisibility(ESlateVisibility::Hidden);
		}

		if(LeaderBoard)
		{
			 LeaderBoardManager = NewObject<ULeaderBoardManager>(); // creates a leaderboard object
			LeaderBoard->AddToViewport(9);
			LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
			if(LeaderBoardManager)
			{
				LeaderBoardManager->CreateLeaderBoard(GetWorld()); // creates the leaderboard array
				
			}
		}
		
if(Timer)
{
	Timer->AddToViewport(7);
}

		if(PauseMenu)
		{
			PauseFunc = Cast<UPauseMenu>(PauseMenu); // instaties the buttons in the pause menu
			PauseFunc->Frozen = false;
			PauseMenu->AddToViewport(10);
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		if (GameOverMenu)
		{
			OverPauseFunc = Cast<UGameOverMenu>(GameOverMenu); // instaties the buttons in the gameover menu
			OverPauseFunc->Frozen = false;
			GameOverMenu->AddToViewport(11);
			GameOverMenu->SetVisibility(ESlateVisibility::Hidden);
		}

		if(PickUp)
		{
			PickUp->AddToViewport(8);
			PickUp->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}
	
}

UUserWidget* AHUDDisplayClass::getCrossDamage() const 
{
	return CrossDamage;
}

void AHUDDisplayClass::Counter()
{
	if(Seconds != 0) // will minus seconds counter if seconds is not 0
	{
		UTextBlock* SecondsAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Seconds")));
		Seconds = Seconds - 1;
		SecondsAmount->SetText(FText::FromString(FString::FromInt(Seconds)));
	}

	else if (Minutes != 0) // will minus minute counter if seconds is 0 nad minutes is not 0
	{
		UTextBlock* MinutesAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Minutes")));
		Minutes = Minutes - 1;
		MinutesAmount->SetText(FText::FromString(FString::FromInt(Minutes)));
		UTextBlock* SecondsAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Seconds")));
		Seconds = 59;
		SecondsAmount->SetText(FText::FromString(FString::FromInt(Seconds)));
	}

	else // will end the game if both minutes and seconds is 0
	{
		APlayerControllerClass* PlayerController = Cast<APlayerControllerClass>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			PlayerController->GameOver();

		}
		
		/// will end game lol
	}
}

void AHUDDisplayClass::AmmoDisplay() // makes the ammo widget visible
{
	Ammo->SetVisibility(ESlateVisibility::Visible);
}

void AHUDDisplayClass::AmmoHide() // hides the ammo widget
{
	Ammo->SetVisibility(ESlateVisibility::Hidden);
}

void AHUDDisplayClass::UpdateAmmo(int32 ammoAmount) // updates the ammo widget when ammo variable is changed
{
	if(Ammo)
	{
		UTextBlock* AmmoAmount = Cast<UTextBlock>(Ammo->GetWidgetFromName(TEXT("Ammo")));
		if(AmmoAmount)
		{
			AmmoAmount->SetText(FText::FromString(FString::FromInt(ammoAmount)));
		}
	}
}

void AHUDDisplayClass::HideCorssDamage(bool hitt) // hides and unhides the widget in the playercontroller class using a bool, true being unhidden and false being hidden
{
	if(CrossDamage)
	{
		CrossDamage->SetVisibility(hitt ? ESlateVisibility::Visible : ESlateVisibility::Hidden);	
	}
	
	
}

void AHUDDisplayClass::UpdateHealthBar(float HealthPercentage)
{
	if (Health)
	{
		UProgressBar* HealthBar = Cast<UProgressBar>(Health->GetWidgetFromName(TEXT("HealthBar")));
		if (HealthBar)
		{
			HealthBar->SetPercent(HealthPercentage);  // Update the progress bar with health percentage
		}

		UTextBlock* HealthText = Cast<UTextBlock>(Health->GetWidgetFromName(TEXT("HealthText")));
		if (HealthText)
		{
			HealthText->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::RoundToInt(HealthPercentage * 100))));
		}
	}
}

void AHUDDisplayClass::MainWeapon() // Change the name of the text widget to the primary weapon if the primirary weapon is visible
{
	if(WeaponType)
	{
		UTextBlock* primaryWep = Cast<UTextBlock>(WeaponType->GetWidgetFromName(TEXT("Weapon")));
		if(primaryWep)
		{
			primaryWep->SetText(FText::FromString(FString::Printf(TEXT("Primary Weapon"))));
		}
	}
}

void AHUDDisplayClass::SecWeapon() // Change the name of the text widget to the secondary weapon if the secondary weapon is visible
{
	if(WeaponType)
	{
		UTextBlock* secWep = Cast<UTextBlock>(WeaponType->GetWidgetFromName(TEXT("Weapon")));
		if(secWep)
		{
			secWep->SetText(FText::FromString(FString::Printf(TEXT("Secondary Weapon"))));
		}
	}
}

void AHUDDisplayClass::displayDeath(bool hitt)
{
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideWidget);
//	GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &UWeaponHandling::HideWidget, 0.5f ,false);
	if(Death)
	{
		Death->SetVisibility(hitt ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void AHUDDisplayClass::TimerDeath() // will get rid of deathUI
{
	displayDeath(false);
}

void AHUDDisplayClass::UpdateLeaderBoard()
{
	//if(!LeaderBoard || !leaderbo)
	UVerticalBox* LeaderBoardList = Cast<UVerticalBox>(LeaderBoard->GetWidgetFromName(TEXT("List"))); // instantiated the list in the leaderboard widget
	LeaderBoardList->ClearChildren(); // clears old data from leaderboard

	const TArray<FLeaderboardStart> & Start = LeaderBoardManager->GetLeaderBoard();

	for(const FLeaderboardStart& Starter: Start)
	{
		UTextBlock* WidgetData = NewObject<UTextBlock>(this); // creates a text box to add each struct
		if(WidgetData)
		{
			WidgetData->SetText(FText::FromString(FString::Printf(TEXT("Player: %s, Kills: %d"), *Starter.Player, Starter.Kills))); // creates a text block in the widget
			LeaderBoardList->AddChild(WidgetData);
		}
	}
}

void AHUDDisplayClass::ShowLeaderBoard() // displays updated leaderboard if player clicks tab
{
	if(isPaused == false)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Visible);
		UpdateLeaderBoard();
	}
	
}

void AHUDDisplayClass::HideLeaderBoard() // hides leaderboard
{
	if(isPaused == false)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void AHUDDisplayClass::UpdatePlayerCount()
{
	LeaderBoardManager->UpdatePlayerKills(1);
	//LeaderBoardManager->UpdateBotKills(1);
	//LeaderboardManager->UpdateBotDeathCount(TEXT("Bot1"), NewBotDeathCount);
	UpdateLeaderBoard();
}

void AHUDDisplayClass::UpdateBotCount(FString Bot) // will update the bots kill depending on which bot got a kill
{
	if(Bot == "Bot 1") 
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 1"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 2")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 2"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 3")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 3"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 4")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 4"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 5")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 5"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 6")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 6"), 1);
		UpdateLeaderBoard();
	}

	if(Bot == "Bot 7")
	{
		LeaderBoardManager->UpdateBotKillCount(TEXT("Bot 7"), 1);
		UpdateLeaderBoard();
	}
	//Death->SetVisibility(ESlateVisibility::Visible);
	
	

	

	
}

void AHUDDisplayClass::PauseGame()
{
	if(PauseFunc->Frozen == false)
	{
		
		PauseFunc->PauseToggle(true); // freezes game
		
	}

	else
	{
		//isPaused = false;
	}


}

void AHUDDisplayClass::HidePuaseMenu() // hides pause screen
{
	LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	isPaused = false;
}

void AHUDDisplayClass::UnHidePasueMenu() // displays pause screen
{
	LeaderBoard->SetVisibility(ESlateVisibility::Visible);
	UpdateLeaderBoard();
	isPaused = true;
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
}

void AHUDDisplayClass::HideGameOverMenu() // hides gameovermenu
{
	if (GameOverMenu)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
		GameOverMenu->SetVisibility(ESlateVisibility::Hidden);

	}

	//GameOverMenu->SetVisibility(ESlateVisibility::Hidden);
	isPaused = false;

}
void AHUDDisplayClass::UnHideGameOverMenu() // displays gameovermenu
{

	if (GameOverMenu)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Visible);
		UpdateLeaderBoard();
		GameOverMenu->SetVisibility(ESlateVisibility::Visible);

	}
	GameOverMenu->SetVisibility(ESlateVisibility::Visible);
	
	isPaused = true;
	//GameOverMenu->SetVisibility(ESlateVisibility::Visible);
}

void AHUDDisplayClass::AmmoDisplay(bool show, FString pick) // will displayPickUpUI depending on which pickup, the player collided to
{
	PickUp->SetVisibility(show ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	UTextBlock* AmmoP = Cast<UTextBlock>(PickUp->GetWidgetFromName(TEXT("PickUp")));
	if(pick =="ammo")
	{
		
		AmmoP->SetText(FText::FromString(FString::Printf(TEXT("Ammo Picked Up"))));
	}

	else if(pick == "wep")
	{
		
		AmmoP->SetText(FText::FromString(FString::Printf(TEXT("Weapon Picked Up"))));
	}

	else if(pick == "hp")
	{
		
		AmmoP->SetText(FText::FromString(FString::Printf(TEXT("Health Picked Up"))));
	}

	else
	{
		AmmoP->SetText(FText::FromString(FString::Printf(TEXT(""))));
	}
	
	
}

void AHUDDisplayClass::AmmoHidden() // hides pickupUI
{
    const FString blank = "";
	AmmoDisplay(false, blank);
}

void AHUDDisplayClass::GameOver() // freezes game to end the round
{
	if (OverPauseFunc && OverPauseFunc->Frozen == false)
	{
		OverPauseFunc->ToggleEndMenu(true);
	}
}






