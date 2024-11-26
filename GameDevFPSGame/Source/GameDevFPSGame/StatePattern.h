// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StatePattern.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class GAMEDEVFPSGAME_API UStatePattern : public UObject
{
	GENERATED_BODY()

public:
   // these methods will be overidden 
	virtual void CreateState(UObject* object){}; // state creation and ending methods 

	virtual void UpdateState(UObject* object){};

	virtual void EndState(UObject* object){};
};

UCLASS()
class GAMEDEVFPSGAME_API UStateIdle : public UStatePattern // idle animation state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	virtual void UpdateState(UObject*) override;

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateWalk : public UStatePattern // Walk animation state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	virtual void UpdateState(UObject*) override;

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateCrouch : public UStatePattern // Crouch input state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateUnCrouch : public UStatePattern // UnCrouch input state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateSprint : public UStatePattern // Sprint input state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateNoSprint : public UStatePattern // UnSprint input state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	

	virtual void EndState(UObject* object)override;
};

UCLASS()
class GAMEDEVFPSGAME_API UStateJump : public UStatePattern // Jump input state
{
	GENERATED_BODY()

public:

	virtual void CreateState(UObject* object) override; // state creation and ending methods 

	

	virtual void EndState(UObject* object)override;
};
