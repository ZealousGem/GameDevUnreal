// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDDisplayClass.h"




void AHUDDisplayClass::BeginPlay()
{
	Super::BeginPlay();

	if(mywidgetClass)
	{
		CrossHair = CreateWidget<UUserWidget>(GetWorld(), mywidgetClass);

		if(CrossHair)
		{
		CrossHair->AddToViewport();	
		}
	}
}
