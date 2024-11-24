// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"

void UMainMenu::StartGameButton()
{

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;

	}
	UGameplayStatics::OpenLevel(this, FName("FPSMap"));

}

void UMainMenu::QuitGameButton()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);


}

void UMainMenu::NativeConstruct()
{

	Super::NativeConstruct();

	UButton* StartGameBut = Cast<UButton>(GetWidgetFromName(TEXT("StartGame")));
	if (StartGameBut)
	{
		StartGameBut->OnClicked.AddDynamic(this, &UMainMenu::StartGameButton);

	}

	UButton* QuitGameBut = Cast<UButton>(GetWidgetFromName(TEXT("QuitGame"))); 
	{
		QuitGameBut->OnClicked.AddDynamic(this, &UMainMenu::QuitGameButton);

	}
}
