// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDisplayClass.h"




void AHUDDisplayClass::BeginPlay()
{
	Super::BeginPlay();

	if(mywidgetClass)
	{
		// allows unreal to access the class through blueprints 
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass);
		CrossDamage = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass2);

		if(CrossHair) // checks if widget has been added
		{
		CrossHair->AddToViewport(2);	
		}
       
		if(mywidgetClass2)
		{
			CrossDamage->AddToViewport(1);
			CrossDamage->SetVisibility(ESlateVisibility::Hidden);
			 // when the program starts it will amke the widget hidden
		}

		
	}
}

UUserWidget* AHUDDisplayClass::getCrossDamage() const
{
	return CrossDamage;
}

void AHUDDisplayClass::HideCorssDamage(bool hitt)
{
	if(CrossDamage)
	{
		CrossDamage->SetVisibility(hitt ? ESlateVisibility::Visible : ESlateVisibility::Hidden);	
	}
	
	
}
