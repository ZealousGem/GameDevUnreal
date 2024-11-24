// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	

	// Check if GetWorld() is valid
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}

	// Attempt to create Title widget
	Title = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass);
	if (!Title)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create Title widget!"));
	}
	else
	{
		Title->AddToViewport(2);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Title widget successfully created and added to viewport."));
	}

	// Attempt to create Menu widget
	Menu = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass2);
	if (!Menu)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to create Menu widget!"));
	}
	else
	{
		Menu->AddToViewport(1);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Menu widget successfully created and added to viewport."));
	}
}
