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
		
			UGameplayStatics::SetGamePaused(World, isPaused);
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if(PlayerController)
		{
			if(isPaused)
			{
				HUD->UnHidePasueMenu();
				FInputModeGameOnly Input;
				PlayerController->SetInputMode(Input);
				PlayerController->DisableInput(PlayerController);
				PlayerController->bShowMouseCursor = true;
				Frozen = true;
			}

			else
			{
				HUD->HidePuaseMenu();
				
				FInputModeGameOnly Input;
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
	
	UAudioManager::GetInstance()->PlaySound2DByName("Explosion", 1.0f);
	PauseToggle(false);
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	UButton* ResumeBut = Cast<UButton>(GetWidgetFromName(TEXT("Resume")));
	if(ResumeBut)
	{
		ResumeBut->OnClicked.AddDynamic(this, &UPauseMenu::ResumeButton);
	}
}

