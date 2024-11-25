// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManager.h"

void UStateManager::SetState(UStatePattern* setState, UObject* object)
{
	if(StateCurrent)
	{
		StateCurrent->EndState(object);
	}

	StateCurrent = setState;
	StateCurrent->CreateState(object);
}

void UStateManager::UpdateState(UObject* object)
{
	StateCurrent->UpdateState(object);
}




