// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDisplayClass.h"
#include "PlayerControllerClass.h"
#include "Components/ProgressBar.h"  // For UProgressBar
#include "Components/TextBlock.h"    // For UTextBlock
#include "GameFrameWork/PlayerController.h"




void AHUDDisplayClass::BeginPlay()
{
	Super::BeginPlay();

	if(mywidgetClass)
	{
		// allows unreal to access the class through blueprints 
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass);
		CrossDamage = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass2);
		Health = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass3);

		if(CrossHair) // checks if widget has been added
		{
		CrossHair->AddToViewport(2);	// sets crosshair under the cross damage layer
		}
       
		if(mywidgetClass2) // same shit as the one before
		{
			CrossDamage->AddToViewport(1); // sets the wdiget layer above the crosshair
			CrossDamage->SetVisibility(ESlateVisibility::Hidden); // hides the widget once the game starts
			 // when the program starts it will amke the widget hidden
		}
		if (Health) // checks if widget has been added
		{
			Health->AddToViewport(3);	// sets crosshair under the cross damage layer
		}

		
	}
	
}

UUserWidget* AHUDDisplayClass::getCrossDamage() const // useless function(i should get rid of this)
{
	return CrossDamage;
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

