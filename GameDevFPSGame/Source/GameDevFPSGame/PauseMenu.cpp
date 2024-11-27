// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"


#include "HUDDisplayClass.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "AudioManager.h"

void UPauseMenu::PauseToggle(bool isPaused)
{
	AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if(UWorld* World = GetWorld())
	{
		
			UGameplayStatics::SetGamePaused(World, isPaused); // function that freezes game
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if(PlayerController)
		{
			if(isPaused)
			{
				HUD->UnHidePasueMenu(); // sets the playercontroller to UI mode and displays the cursor
				FInputModeGameOnly Input;
				PlayerController->SetInputMode(Input);
				PlayerController->DisableInput(PlayerController);
				PlayerController->bShowMouseCursor = true;
				Frozen = true;
			}

			else
			{
				HUD->HidePuaseMenu();
				
				FInputModeGameOnly Input; // sets playercontroller to input mode and hides mouse cursor
				PlayerController->SetInputMode(Input);
				Frozen = false;
				PlayerController->bShowMouseCursor = false; 
				PlayerController->EnableInput(PlayerController);
			}
		}

		
	}
}

void UPauseMenu::ResumeButton()
{
	
	
	PauseToggle(false);
}

void UPauseMenu::QuitGame()
{
	PauseToggle(false);
	UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	UButton* ResumeBut = Cast<UButton>(GetWidgetFromName(TEXT("Resume"))); // finds resume button in the wdiget
	UButton* QuitBut = Cast<UButton>(GetWidgetFromName(TEXT("Quit")));
	if(ResumeBut)
	{
		ResumeBut->OnClicked.AddDynamic(this, &UPauseMenu::ResumeButton); // instatites button
	}

	if(QuitBut)
	{
		QuitBut->OnClicked.AddDynamic(this, &UPauseMenu::QuitGame);
	}
}

