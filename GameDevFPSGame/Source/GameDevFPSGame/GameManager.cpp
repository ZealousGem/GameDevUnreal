// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

void UGameManager::AssignObserver(TScriptInterface<IObserver> Observer) // adds an observer to the assinged obser list
{
	if(Observer)
	{
		Observers.Add(Observer);
	}
}

void UGameManager::AssignObserverWeapon(TScriptInterface<IObserverWeapon> ObserverWep)
{
	if(ObserverWep)
	{
		ObserverWeps.Add(ObserverWep);
	}
}

void UGameManager::AssignObserverHP(TScriptInterface<IObserverHP> Observerhp)
{
	if(Observerhp)
	{
		ObserverHPs.Add(Observerhp);
	}
}

void UGameManager::notifyChange() // will tell all observers in the list that there has been a change
{
	for(TScriptInterface<IObserver> Observer : Observers)
	{
		
		if(Observer)
		{
			IObserver* ObsObject = Cast<IObserver>(Observer.GetObject());

			if(ObsObject)
			{
				ObsObject->PickitUp();
			}
		}
	}

	for(TScriptInterface<IObserverWeapon> ObserverWeapon : ObserverWeps)
	{
		if(ObserverWeapon)
		{
			IObserverWeapon* Wep = Cast<IObserverWeapon>(ObserverWeapon.GetObject());
			if(Wep)
			{
				Wep->newWeapon();
			}
			
		}
	}

	for(TScriptInterface<IObserverHP> ObserverHP : ObserverHPs)
	{
		if(ObserverHP)
		{
			IObserverHP* Wepo = Cast<IObserverHP>(ObserverHP.GetObject());
			if(Wepo)
			{
				;Wepo->YouDied();
			}
			
		}
	}
}
