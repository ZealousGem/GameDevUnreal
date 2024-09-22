// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDisplayClass.h"
#include "PlayerControllerClass.h"
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

