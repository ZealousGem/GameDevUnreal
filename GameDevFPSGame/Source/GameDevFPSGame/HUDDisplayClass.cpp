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
		Ammo = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass4);
		WeaponType = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass5);
		Death = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass6);
		LeaderBoard = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass7);

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
			LeaderBoard->AddToViewport(7);
			LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
		}
		

		
	}
	
}

UUserWidget* AHUDDisplayClass::getCrossDamage() const 
{
	return CrossDamage;
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

void AHUDDisplayClass::ShowLeaderBoard()
{
	LeaderBoard->SetVisibility(ESlateVisibility::Visible);
}

void AHUDDisplayClass::HideLeaderBoard()
{
	LeaderBoard->SetVisibility(ESlateVisibility::Hidden);
}



