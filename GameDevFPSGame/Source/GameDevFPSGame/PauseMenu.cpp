// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


void UPauseMenu::ResumeGame()
{

	// Resume the game
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// Reset input mode and hide the mouse cursor
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;

	}
	RemoveFromParent();

}

void UPauseMenu::QuitToMainMenu()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf
	(TEXT("QuitTomainMenu")));

}
void UPauseMenu::RestartLevel()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf
	(TEXT("Restart level")));

}


