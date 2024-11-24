// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverMenu.h"


#include "HUDDisplayClass.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UGameOverMenu::ToggleEndMenu(bool isPaused)
{
    AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());
    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::SetGamePaused(World, isPaused);

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            if (isPaused)
            {
                if (HUD)
                {
                    HUD->UnHideGameOverMenu();
                }

                FInputModeUIOnly InputMode;
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = true;
                Frozen = true;
            }
            else
            {
                if (HUD)
                {
                    HUD->HideGameOverMenu();
                }

                FInputModeGameOnly InputMode;
                PlayerController->SetInputMode(InputMode);
                PlayerController->bShowMouseCursor = false;
                Frozen = false;
            }
        }
    }
}

void UGameOverMenu::RestartButton()
{
    // Restart the current level
    ToggleEndMenu(false);
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void UGameOverMenu::QuitButton()
{
    // Quit the game
    ToggleEndMenu(false);
    UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UGameOverMenu::MainMenuButton()
{
    // Go to the main menu
    ToggleEndMenu(false);
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGameOverMenu::NativeConstruct()
{
    Super::NativeConstruct();

    // Bind the Restart button
    UButton* RestartBut = Cast<UButton>(GetWidgetFromName(TEXT("Restart")));
    if (RestartBut)
    {
        RestartBut->OnClicked.AddDynamic(this, &UGameOverMenu::RestartButton);
    }

    // Bind the Quit button
    UButton* QuitBut = Cast<UButton>(GetWidgetFromName(TEXT("Quit")));
    if (QuitBut)
    {
        QuitBut->OnClicked.AddDynamic(this, &UGameOverMenu::QuitButton);
    }

    // Bind the Main Menu button
    UButton* MainMenuBut = Cast<UButton>(GetWidgetFromName(TEXT("MainMenu")));
    if (MainMenuBut)
    {
        MainMenuBut->OnClicked.AddDynamic(this, &UGameOverMenu::MainMenuButton);
    }
}
