// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDevFPSGame/Public/WidgetBase.h"

#if WITH_EDITOR
const FText UWidgetBase::GetPaletteCategory()
{
	return NSLOCTEXT("UMG", "CustomPalletteCateogry", "GameDev!");
}
#endif


