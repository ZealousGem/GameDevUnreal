// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Observer.h"
#include "GameManager.generated.h"


/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UGameManager : public UObject
{
	GENERATED_BODY()

public:

	void AssignObserver(TScriptInterface<IObserver> Observer); // assigns an observer

	void AssignObserverWeapon(TScriptInterface<IObserverWeapon> ObserverWep);

	void notifyChange(); // tells all the assigned obersers there was a change

private:
	
	TArray<TScriptInterface<IObserver>>Observers; // to contain more than one assigned observer

	TArray<TScriptInterface<IObserverWeapon>> ObserverWeps; 
};
