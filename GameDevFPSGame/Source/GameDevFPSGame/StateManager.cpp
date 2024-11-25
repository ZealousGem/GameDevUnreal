// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManager.h"

void UStateManager::SetState(UStatePattern* setState, UObject* object) // changes old state to new one
{
	if(setState)
	{
		if(StateCurrent)
		{
			StateCurrent->EndState(object);
		
		}
		StateCurrent = setState;
		StateCurrent->CreateState(object);
		
	}
	

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetState called with a null setState"));
	}
	
}

void UStateManager::UpdateState(UObject* object) // update state animation
{
	StateCurrent->UpdateState(object);
}




