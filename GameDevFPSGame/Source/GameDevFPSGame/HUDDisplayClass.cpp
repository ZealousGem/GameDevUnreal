// Fill out your copyright notice in the Description page of Project Settings.


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
			 LeaderBoardManager = NewObject<ULeaderBoardManager>();
			LeaderBoard->AddToViewport(8);
			LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
			if(LeaderBoardManager)
			{
				LeaderBoardManager->CreateLeaderBoard(GetWorld());
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf
					(TEXT("Leaderboard made")));
			}
		}
		
if(Timer)
{
	Timer->AddToViewport(7);
}

		if(PauseMenu)
		{
			PauseFunc = Cast<UPauseMenu>(PauseMenu);
			PauseFunc->Frozen = false;
			PauseMenu->AddToViewport(9);
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		if (GameOverMenu)
		{
			OverPauseFunc = Cast<UGameOverMenu>(GameOverMenu);
			OverPauseFunc->Frozen = false;
			GameOverMenu->AddToViewport(10);
			GameOverMenu->SetVisibility(ESlateVisibility::Hidden);
		}
		
	}
	
}

UUserWidget* AHUDDisplayClass::getCrossDamage() const 
{
	return CrossDamage;
}

void AHUDDisplayClass::Counter()
{
	if(Seconds != 0)
	{
		UTextBlock* SecondsAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Seconds")));
		Seconds = Seconds - 1;
		SecondsAmount->SetText(FText::FromString(FString::FromInt(Seconds)));
	}

	else if (Minutes != 0)
	{
		UTextBlock* MinutesAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Minutes")));
		Minutes = Minutes - 1;
		MinutesAmount->SetText(FText::FromString(FString::FromInt(Minutes)));
		UTextBlock* SecondsAmount = Cast<UTextBlock>(Timer->GetWidgetFromName(TEXT("Seconds")));
		Seconds = 59;
		SecondsAmount->SetText(FText::FromString(FString::FromInt(Seconds)));
	}

	else
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

void AHUDDisplayClass::TimerDeath()
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

void AHUDDisplayClass::ShowLeaderBoard()
{
	if(isPaused == false)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Visible);
		UpdateLeaderBoard();
	}
	
}

void AHUDDisplayClass::HideLeaderBoard()
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

void AHUDDisplayClass::UpdateBotCount(FString Bot)
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
		
		PauseFunc->PauseToggle(true);
		
	}

	else
	{
		//isPaused = false;
	}


}

void AHUDDisplayClass::HidePuaseMenu()
{
	LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	isPaused = false;
}

void AHUDDisplayClass::UnHidePasueMenu()
{
	LeaderBoard->SetVisibility(ESlateVisibility::Visible);
	UpdateLeaderBoard();
	isPaused = true;
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
}

void AHUDDisplayClass::HideGameOverMenu()
{
	if (GameOverMenu)
	{
		LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
		GameOverMenu->SetVisibility(ESlateVisibility::Hidden);

	}

	//GameOverMenu->SetVisibility(ESlateVisibility::Hidden);
	isPaused = false;

}
void AHUDDisplayClass::UnHideGameOverMenu()
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

void AHUDDisplayClass::GameOver()
{
	if (OverPauseFunc && OverPauseFunc->Frozen == false)
	{
		OverPauseFunc->ToggleEndMenu(true);
	}
}






