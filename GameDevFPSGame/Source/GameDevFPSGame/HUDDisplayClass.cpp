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
		CrossHair->AddToViewport();	
		}
       
		if(mywidgetClass2 && hit)
		{
			CrossDamage->AddToViewport();
		}

		
	}
}
